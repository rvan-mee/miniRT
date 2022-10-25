/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   work.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 17:47:20 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/25 17:47:10 by rvan-mee      ########   odam.nl         */
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

static void	free_data(t_minirt *data, t_jobs *current_job)
{
	quit_working(data);
	free(current_job);
	pthread_mutex_lock(&data->thread.job_lock);
	clear_job_lst(data);
	mlx_close_window(data->mlx);
	pthread_mutex_unlock(&data->thread.job_lock);
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
			if (!create_rays(data, current_job))
			{
				free_data(data, current_job);
				break ;
			}
			if (!render(data, current_job))
				quit_working(data);
			clean_rays(current_job->rays);
			free(current_job);
		}
	}
	return (NULL);
}
