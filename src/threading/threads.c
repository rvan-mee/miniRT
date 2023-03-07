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

static bool	destroy_locks(t_minirt *data)
{
	pthread_cond_destroy(&data->thread.done_cond);
	pthread_cond_destroy(&data->thread.stop_cond);
	pthread_mutex_destroy(&data->thread.quit_lock);
	pthread_mutex_destroy(&data->thread.job_lock);
	return (false);
}

static bool	init_locks(t_minirt *data)
{
	if (pthread_cond_init(&data->thread.done_cond, NULL) ||
		pthread_cond_init(&data->thread.stop_cond, NULL) ||
		pthread_mutex_init(&data->thread.quit_lock, NULL) ||
		pthread_mutex_init(&data->thread.job_lock, NULL))
		return (destroy_locks(data));
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
	destroy_locks(data);
}

static bool	create_threads(t_minirt *data, t_threading *thread)
{
	size_t	*i;

	i = &thread->created_threads;
	pthread_mutex_lock(&thread->quit_lock);
	while (thread->created_threads < THREAD_C)
	{
		if (pthread_create(&thread->threads[*i], NULL, work, data))
		{
			thread->quit = true;
			pthread_mutex_unlock(&data->thread.quit_lock);
			join_threads(data);
			return (false);
		}
		thread->created_threads++;
	}
	pthread_mutex_unlock(&thread->quit_lock);
	return (true);
}

bool	init_work_threads(t_minirt *data)
{
	t_threading	*thread;

	thread = &data->thread;
	wipe_image(data);
	if (!init_locks(data))
		return (false);
	if (!create_render_queue(data))
		return (destroy_locks(data));
	if (!create_threads(data, thread))
		return (false);
	thread->render_start = get_time_ms();
	return (true);
}
