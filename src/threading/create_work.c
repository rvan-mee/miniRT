/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_work.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 18:35:59 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/24 20:15:38 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <libft.h>

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

// is it faster to go >>> down <<< down >>>
// or >>> down reset left >>> down reset left >>>
bool	create_work(t_minirt *data)
{
	const size_t	x_diff[2] = {data->width / THREAD_C, data->width % THREAD_C};
	const size_t	y_diff[2] = {data->height / THREAD_C, data->height % THREAD_C};
	size_t			start[2];
	size_t			end[2];

	start[X] = 0;
	start[Y] = 0;
	end[Y] = y_diff[0];
	while (start[Y] < data->height)
	{
		start[X] = 0;
		end[X] = x_diff[0];
		while (end[X] - x_diff[0] + x_diff[1] < data->width)
		{
			if (data->width - end[X] == x_diff[1])
				end[X] += x_diff[1];
			if (!lst_add(&data->thread.job_lst, new_job_node(data, start, end)))
				return (false); // clear list
			// printf("creating work: start: %zu %zu  end: %zu %zu\n", start[Y], start[X], end[Y], end[X]);
			start[X] += x_diff[0];
			end[X] += x_diff[0];
		}
		start[Y] += y_diff[0];
		end[Y] += y_diff[0];
		if (data->height - end[Y] == y_diff[1])
			end[Y] += y_diff[1];
	}
	return (true);
}
