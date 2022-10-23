/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   work.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 17:47:20 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/23 19:04:11 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <unistd.h>

#include <stdio.h>
void	clear_lob_lst(t_minirt *data)
{
	t_jobs	*tmp;
	t_jobs	*tmp_next;

	tmp_next = NULL;
	tmp = data->thread.job_lst;
	data->thread.job_lst = NULL;
	if (tmp)
		tmp_next = tmp->next_job;
	while (tmp && tmp_next)
	{
		free_job_node(tmp);
		tmp = tmp_next;
	}
	free_job_node(tmp);
}

bool	reset_work(t_minirt *data)
{
	pthread_mutex_lock(&data->thread.job_lock);
	static int n2 = 0;
	dprintf(1, "resetting work %d\n", ++n2);
	clear_lob_lst(data);
	wipe_image(data);
	create_work(data);
	static int n = 0;
	dprintf(1, "done resetting work for the %d'th time\n", ++n);
	if (!data->thread.job_lst)
	{
		pthread_mutex_unlock(&data->thread.job_lock);
		return (false);
	}
	pthread_mutex_unlock(&data->thread.job_lock);
	return (true);
}

bool	keep_working(t_threading *thread)
{
	bool	should_work;

	pthread_mutex_lock(&thread->quit_lock);
	should_work = !thread->quit;
	pthread_mutex_unlock(&thread->quit_lock);
	return (should_work);
}

void	quit_working(t_minirt *data)
{
	pthread_mutex_lock(&data->thread.quit_lock);
	data->thread.quit = true;
	pthread_mutex_unlock(&data->thread.quit_lock);
}

static void	wait_for_new_job(t_minirt *data)
{
	bool	locked;

	locked = false;
	while (keep_working(&data->thread))
	{
		pthread_mutex_lock(&data->thread.job_lock);
		locked = true;
		if (data->thread.job_lst)
			break ;
		pthread_mutex_unlock(&data->thread.job_lock);
		locked = false;
		usleep(50);
	}
	if (locked)
		pthread_mutex_unlock(&data->thread.job_lock);
}

void	*work(void *param)
{
	t_minirt	*data;
	t_jobs		*current_job;

	data = param;
	while (keep_working(&data->thread))
	{
		pthread_mutex_lock(&data->thread.job_lock);
		current_job = get_and_remove_first_node_from_list(&data->thread.job_lst);
		pthread_mutex_unlock(&data->thread.job_lock);
		if (!current_job)
			wait_for_new_job(data);
		else
		{
			render(data, current_job);
			free_job_node(current_job);
		}
	}
	return (NULL);
}
