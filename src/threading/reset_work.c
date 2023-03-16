/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_work.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:27:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/09 19:49:54 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <libft.h>

void	wipe_image(t_minirt *data)
{
	ft_bzero(data->img->pixels, data->height * data->width * sizeof(uint32_t));
}

void	wait_till_done(t_minirt *data)
{
	pthread_mutex_lock(&data->thread.quit_lock);
	while (data->thread.threads_done != data->thread.created_threads)
		pthread_cond_wait(&data->thread.done_cond, &data->thread.quit_lock);
	pthread_mutex_unlock(&data->thread.quit_lock);
}

bool	reset_work(t_minirt *data)
{
	wipe_image(data);
	if (!create_render_queue(data))
		return (false);
	data->thread.render_start = get_time_ms();
	stop_working(&data->thread, false);
	return (true);
}
