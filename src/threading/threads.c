/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 14:40:05 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/26 21:44:44 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <mlx.h>
#include <libft.h>

static void	destroy_mutexes(t_minirt *data)
{
	pthread_mutex_destroy(&data->thread.quit_lock);
	pthread_mutex_destroy(&data->thread.job_lock);
}

void	join_threads(t_minirt *data)
{
	size_t	i;

	i = 0;
	while (i < data->thread.created_threads)
	{
		pthread_join(data->thread.threads[i], NULL);
		i++;
	}
	destroy_mutexes(data);
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
	create_render_queue(data);
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
