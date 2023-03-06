/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   work_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:37:23 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/24 15:03:49 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <unistd.h>

void	quit_working(t_minirt *data)
{
	pthread_mutex_lock(&data->thread.quit_lock);
	data->thread.quit = true;
	pthread_mutex_unlock(&data->thread.quit_lock);
}

bool	keep_working(t_threading *thread)
{
	bool	should_work;

	pthread_mutex_lock(&thread->quit_lock);
	should_work = !thread->quit;
	pthread_mutex_unlock(&thread->quit_lock);
	return (should_work);
}

void	wait_for_new_job(t_minirt *data)
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
		usleep(1000);
	}
	if (locked)
		pthread_mutex_unlock(&data->thread.job_lock);
}
