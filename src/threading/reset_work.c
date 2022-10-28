/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_work.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:27:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/28 15:00:35 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <libft.h>

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

bool	reset_work(t_minirt *data)
{
	clear_job_lst(data);
	wipe_image(data);
	create_render_queue(data);
	if (!data->thread.job_lst)
		return (false);
	return (true);
}
