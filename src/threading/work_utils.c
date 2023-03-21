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
#include <sys/time.h>

void	quit_working(t_threading *thread)
{
	pthread_mutex_lock(&thread->quit_lock);
	thread->quit = true;
	thread->stop = false;
	pthread_cond_broadcast(&thread->stop_cond);
	pthread_mutex_unlock(&thread->quit_lock);
}

void	stop_working(t_threading *thread, bool stop)
{
	pthread_mutex_lock(&thread->quit_lock);
	thread->stop = stop;
	if (!stop)
		pthread_cond_broadcast(&thread->stop_cond);
	pthread_mutex_unlock(&thread->quit_lock);
}

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
