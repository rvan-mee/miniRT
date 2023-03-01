/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 14:40:05 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/09 19:23:55 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <libft.h>

static void	destroy_mutexes(t_minirt *data)
{
	pthread_mutex_destroy(&data->thread.quit_lock);
	pthread_mutex_destroy(&data->thread.job_lock);
	pthread_mutex_destroy(&data->thread.ref_lock);
}

static bool	init_mutexes(t_minirt *data)
{
	if (pthread_mutex_init(&data->thread.quit_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->thread.ref_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->thread.quit_lock);
		return (false);
	}
	if (pthread_mutex_init(&data->thread.job_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->thread.ref_lock);
		pthread_mutex_destroy(&data->thread.quit_lock);
		return (false);
	}
	return (true);
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
	data->thread.ref_count = 0;
	thread = &data->thread.created_threads;
	wipe_image(data);
	if (!init_mutexes(data))
		return (false);
	create_render_queue(data);
	pthread_mutex_lock(&data->thread.quit_lock);
	data->thread.quit = false;
	while (*thread < THREAD_C)
	{
		if (pthread_create(&data->thread.threads[*thread], NULL, work, data) != 0)
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
