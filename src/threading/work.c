/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   work.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 17:47:20 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/24 20:14:33 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <stdlib.h>

static t_jobs	*take_first_node(t_jobs **head)
{
	t_jobs	*first_node;

	first_node = *head;
	if (first_node)
		*head = (*head)->next_job;
	return (first_node);
}

void	*work(void *param)
{
	t_minirt	*data;
	t_jobs		*current_job;

	data = param;
	while (keep_working(&data->thread))
	{
		pthread_mutex_lock(&data->thread.job_lock);
		current_job = take_first_node(&data->thread.job_lst);
		pthread_mutex_unlock(&data->thread.job_lock);
		if (!current_job)
			wait_for_new_job(data);
		else
		{
			if (!create_rays(data, current_job))
			{
				// clear stuff & quit
			}
			if (!render(data, current_job))
				quit_working(data);
			clean_rays(current_job->rays);
			free(current_job);
		}
	}
	return (NULL);
}
