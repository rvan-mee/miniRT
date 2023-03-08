/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   work.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 17:47:20 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/09 19:50:31 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <stdlib.h>
#include <inttypes.h>

static t_jobs	*take_first_node(t_minirt *data)
{
	t_jobs	*first_node;

	pthread_mutex_lock(&data->thread.job_lock);
	first_node = data->thread.job_lst;
	if (first_node)
		data->thread.job_lst = data->thread.job_lst->next_job;
	pthread_mutex_unlock(&data->thread.job_lock);
	return (first_node);
}

static void	pause_thread(t_threading *thread)
{
	thread->threads_done++;
	if (thread->threads_done == thread->created_threads)
	{
		printf("All threads done after %"PRIu64"\n",
			get_time_ms() - thread->render_start);
		pthread_cond_broadcast(&thread->done_cond);
	}
	while (thread->stop)
		pthread_cond_wait(&thread->stop_cond, &thread->quit_lock);
	thread->threads_done--;
}

static bool	keep_working(t_threading *thread)
{
	pthread_mutex_lock(&thread->quit_lock);
	if (thread->stop)
		pause_thread(thread);
	if (thread->quit)
		return (pthread_mutex_unlock(&thread->quit_lock), false);
	pthread_mutex_unlock(&thread->quit_lock);
	return (true);
}

void	*work(void *param)
{
	t_minirt	*data;
	t_jobs		*current_job;

	data = param;
	while (keep_working(&data->thread))
	{
		current_job = take_first_node(data);
		if (current_job == NULL)
		{
			stop_working(&data->thread, true);
			continue;
		}
		current_job->job(data, current_job->job_param);
		free(current_job);
	}
	return (NULL);
}
