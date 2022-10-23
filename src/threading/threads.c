/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 14:40:05 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/23 17:02:45 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <mlx.h>
#include <libft.h>

void	wipe_image(t_minirt *data)
{
	ft_bzero(data->img->pixels, data->height * data->width * sizeof(uint32_t));
}

void	destroy_mutexes(t_minirt *data)
{
	pthread_mutex_destroy(&data->thread.quit_lock);
	pthread_mutex_destroy(&data->thread.job_lock);
}

#include <stdio.h>
void	join_threads(t_minirt *data)
{
	size_t	i;

	i = 0;
	printf("joining threads\n");
	while (i < data->thread.created_threads)
	{
		pthread_join(data->thread.threads[i], NULL);
		i++;
	}
	destroy_mutexes(data);
}
void	print_jobs(t_minirt *data)
{
	t_jobs	*tmp;
	size_t	i;

	i = 0;
	tmp = data->thread.job_lst;
	while (tmp)
	{
		printf("block %zu %zu %zu, %zu %zu\n", i, tmp->start_pixels[Y], tmp->start_pixels[X], tmp->end_pixels[Y], tmp->end_pixels[X]);
		tmp = tmp->next_job;
		i++;
	}
}

bool	init_work_threads(t_minirt *data)
{
	size_t	*thread;

	data->thread.created_threads = 0;
	thread = &data->thread.created_threads;
	wipe_image(data);
	if (pthread_mutex_init(&data->thread.quit_lock, NULL) == -1)
		return (false);
	if (pthread_mutex_init(&data->thread.job_lock, NULL) == -1)
		return (pthread_mutex_destroy(&data->thread.quit_lock), false);
	// reset_work(data);
	create_work(data);
	// print_jobs(data);
	pthread_mutex_lock(&data->thread.quit_lock);
	data->thread.quit = false;
	while (*thread < THREAD_C)
	{
		if (pthread_create(&data->thread.threads[*thread], NULL, work, data) == -1)
		{
			data->thread.quit = true;
			pthread_mutex_unlock(&data->thread.quit_lock);
			join_threads(data);
			return (false);
		}
		*thread += 1;
	}
	pthread_mutex_unlock(&data->thread.quit_lock);
	return (true);
}
