/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_work.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 18:35:59 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/23 20:21:17 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <dynarr.h>
#include <ft_math.h>
#include <math.h>
#include <minirt.h>
#include <stdlib.h>
#include <libft.h>

#include <stdio.h>
#define ASPECT_RATIO	0
#define PIXELS_WIDTH	1
#define PIXELS_HEIGHT	2

static void	clean_rays(t_ray **rays)
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

// Does NOT free
t_jobs	*get_and_remove_first_node_from_list(t_jobs **head)
{
	t_jobs	*first_node;

	first_node = *head;
	if (first_node)
		*head = (*head)->next_job;
	return (first_node);
}

void	free_job_node(t_jobs *jobs)
{
	if (jobs)
		clean_rays(jobs->rays);
	free(jobs);
}

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

t_ray	calculate_primary_ray(t_minirt *data, size_t x, size_t y)
{
	const float	params[] = {\
		[ASPECT_RATIO] = (float) data->width / (float) data->height, \
		[PIXELS_WIDTH] = tanf(data->scene.camera.camera.fov / 2), \
		[PIXELS_HEIGHT] = params[PIXELS_WIDTH] / params[ASPECT_RATIO]
	};
	t_ray	ray;
	t_fvec	coords;

	ray.origin = data->scene.camera.camera.coords;
	// use offset from camera direction
	coords[X] = ((float) x + 0.5f) / (float) data->width;
	coords[Y] = ((float) y + 0.5f) / (float) data->height;
	coords[X] = 2 * coords[X] - 1;
	coords[Y] = 1 - 2 * coords[Y];
	coords[X] *= params[PIXELS_WIDTH];
	coords[Y] *= params[PIXELS_HEIGHT];
	coords[Z] = 1;
	ray.direction = normalize_vector(coords);
	// printf("%f %f %f\n", ray.direction[X], ray.direction[Y], ray.direction[Z]);
	return (ray);
}

static bool		allocate_rays(t_jobs *node, size_t x, size_t y)
{
	size_t	i;

	i = 0;
	node->rays = ft_calloc(y + 1, sizeof(t_ray *));
	if (!node->rays)
		return (false);
	node->rays[y] = NULL;
	while (i < y)
	{
		node->rays[i] = malloc(sizeof(t_ray) * (x + 1));
		if (!node->rays[i])
			return (clean_rays(node->rays), false);
		// node->rays[i][x] = NULL;
		i++;
	}
	return (true);
}

static t_jobs	*new_job_node(t_minirt *data, size_t start[2], size_t end[2])
{
	const size_t	size[2] = {end[X] - start[X], end[Y] - start[Y]};
	t_jobs			*new_node;
	size_t			x;
	size_t			y;
	size_t			i;

	i = 0;
	new_node = malloc(sizeof(t_jobs));
	if (!new_node)
		return (NULL);
	new_node->next_job = NULL;
	if (!allocate_rays(new_node, size[X], size[Y]))
		return (free(new_node), NULL);
	new_node->start_pixels[X] = start[X];
	new_node->start_pixels[Y  ]= start[Y];
	new_node->end_pixels[X] = end[X];
	new_node->end_pixels[Y]= end[Y];
	y = start[Y];
	while (y < end[Y])
	{
		x = start[X];
		while (x < end[X])
		{
			new_node->rays[y - start[Y]][x - start[X]] = calculate_primary_ray(data, x, y);
			x++;
		}
		y++;
	}
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

	start[Y] = 0;
	end[Y] = y_diff[0];
	start[X] = 0;
	start[Y] = 0;
	// end[X] = 1920; // tmp testing
	// end[Y] = 1080;
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
