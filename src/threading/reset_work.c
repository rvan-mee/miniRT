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
#include <unistd.h>

void	wipe_image(t_minirt *data)
{
	ft_bzero(data->img->pixels, data->height * data->width * sizeof(uint32_t));
}

void	clean_rays(t_ray **rays)
{
	size_t	i;

	i = 0;
	if (!rays)
		return ;
	while (rays[i])
	{
		free(rays[i]);
		i++;
	}
	free(rays);
}

void	clear_job_lst(t_minirt *data)
{
	t_jobs	*to_free;
	t_jobs	*to_free_next;

	to_free_next = NULL;
	to_free = data->thread.job_lst;
	data->thread.job_lst = NULL;
	if (to_free)
		to_free_next = to_free->next_job;
	while (to_free && to_free_next)
	{
		free(to_free->job_param);
		free(to_free);
		to_free = to_free_next;
		to_free_next = to_free->next_job;
	}
	if (to_free)
		free(to_free->job_param);
	free(to_free);
}

void	wait_till_done(t_minirt *data)
{
	bool	do_break;

	do_break = false;
	while (1)
	{
		pthread_mutex_lock(&data->thread.ref_lock);
		if (data->thread.ref_count == 0)
			do_break = true;
		pthread_mutex_unlock(&data->thread.ref_lock);
		if (do_break)
			break ;
		usleep(100);
	}
}

bool	reset_work(t_minirt *data)
{
	wipe_image(data);
	create_render_queue(data);
	if (!data->thread.job_lst)
		return (false);
	return (true);
}
