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

static void	ref(t_threading *thread)
{
	pthread_mutex_lock(&thread->ref_lock);
	thread->ref_count++;
	pthread_mutex_unlock(&thread->ref_lock);
}

static void	unref(t_threading *thread)
{
	pthread_mutex_lock(&thread->ref_lock);
	thread->ref_count--;
	pthread_mutex_unlock(&thread->ref_lock);
}

void	*work(void *param)
{
	t_minirt	*data;
	t_jobs		*current_job;

	data = param;
	while (keep_working(&data->thread))
	{
		current_job = take_first_node(data);
		if (!current_job)
			wait_for_new_job(data);
		else
		{
			ref(&data->thread);
			current_job->job(data, current_job->job_param);
			unref(&data->thread);
			free(current_job);
		}
	}
	return (NULL);
}
