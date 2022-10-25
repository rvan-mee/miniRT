/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_work.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 18:35:59 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/25 18:02:43 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <libft.h>

#define DIFF 1

static bool	lst_add(t_jobs **head, t_jobs *new)
{
	t_jobs	*tmp;

	tmp = *head;
	if (!new)
		return (false);
	if (!tmp)
	{
		*head = new;
		return (true);
	}
	while (tmp->next_job)
		tmp = tmp->next_job;
	tmp->next_job = new;
	return (true);
}

static t_jobs	*new_job_node(t_minirt *data, size_t start[2], size_t end[2])
{
	t_jobs			*new_node;

	new_node = ft_calloc(1, sizeof(t_jobs));
	if (!new_node)
		return (NULL);
	new_node->next_job = NULL;
	new_node->start_pixels[X] = start[X];
	new_node->start_pixels[Y] = start[Y];
	new_node->end_pixels[X] = end[X];
	new_node->end_pixels[Y] = end[Y];
	new_node->size[X] = end[X] - start[X];
	new_node->size[Y] = end[Y] - start[Y];
	new_node->camera.coords = data->scene.camera.camera.coords;
	new_node->camera.fov = data->scene.camera.camera.fov;
	new_node->camera.orientation = data->scene.camera.camera.orientation;
	return (new_node);
}

static void	set_offset(t_minirt *data, size_t offset[3])
{
	const size_t	width = data->width;
	const size_t	height = data->height;

	if (height < width)
		offset[0] = height / BLOCK_C;
	else
		offset[0] = width / BLOCK_C;
	offset[X + DIFF] = width % offset[0];
	offset[Y + DIFF] = height % offset[0];
}

// function for norm :/
static void	increment(size_t *start, size_t *end, size_t *offset, int coord)
{
	if (coord == X)
	{
		start[X] = end[X];
		end[X] += offset[0];
		return ;
	}
	start[Y] = end[Y];
	end[Y] += offset[0];
}

// is it faster to go >>> down <<< down >>>
// or >>> down reset left >>> down reset left >>>
bool	create_work(t_minirt *data)
{
	size_t	offset[3];
	size_t	start[2];
	size_t	end[2];

	set_offset(data, offset);
	start[Y] = 0;
	end[Y] = offset[0];
	while (end[Y] <= data->height)
	{
		start[X] = 0;
		end[X] = offset[0];
		if (end[Y] + offset[0] > data->height)
			end[Y] += offset[Y + DIFF];
		while (end[X] <= data->width)
		{
			if (end[X] + offset[0] > data->width)
				end[X] += offset[X + DIFF];
			if (!lst_add(&data->thread.job_lst, new_job_node(data, start, end)))
				return (clear_job_lst(data), false);
			increment(start, end, offset, X);
		}
		increment(start, end, offset, Y);
	}
	return (true);
}
