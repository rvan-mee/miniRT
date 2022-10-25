/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_rays.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:56:11 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/25 18:02:13 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <ft_math.h>
#include <math.h>
#include <stdlib.h>
#include <libft.h>

#define ASPECT_RATIO	0
#define PIXELS_WIDTH	1
#define PIXELS_HEIGHT	2

static t_ray	get_ray(t_minirt *data, t_jobs *job, size_t x, size_t y)
{
	const float	params[] = {\
		[ASPECT_RATIO] = (float) data->width / (float) data->height, \
		[PIXELS_WIDTH] = tanf(job->camera.fov / 2), \
		[PIXELS_HEIGHT] = params[PIXELS_WIDTH] / params[ASPECT_RATIO]
	};
	t_ray		ray;
	t_fvec		coords;

	ray.origin = job->camera.coords;
	// use offset from camera direction
	coords[X] = ((float) x + 0.5f) / (float) data->width;
	coords[Y] = ((float) y + 0.5f) / (float) data->height;
	coords[X] = 2 * coords[X] - 1;
	coords[Y] = 1 - 2 * coords[Y];
	coords[X] *= params[PIXELS_WIDTH];
	coords[Y] *= params[PIXELS_HEIGHT];
	coords[Z] = 1;
	ray.direction = normalize_vector(coords);
	return (ray);
}

static bool	allocate_rays(t_jobs *node)
{
	size_t	i;

	i = 0;
	node->rays = ft_calloc(node->size[Y] + 1, sizeof(t_ray *));
	if (!node->rays)
		return (false);
	while (i < node->size[Y])
	{
		node->rays[i] = malloc(sizeof(t_ray) * (node->size[X] + 1));
		if (!node->rays[i])
			return (clean_rays(node->rays), false);
		i++;
	}
	return (true);
}

bool	create_rays(t_minirt *data, t_jobs *job)
{
	size_t	start[2];
	size_t	end[2];
	size_t	x;
	size_t	y;

	start[X] = job->start_pixels[X];
	start[Y] = job->start_pixels[Y];
	end[X] = job->end_pixels[X];
	end[Y] = job->end_pixels[Y];
	if (!allocate_rays(job))
		return (false);
	y = start[Y];
	while (y < end[Y])
	{
		x = start[X];
		while (x < end[X])
		{
			job->rays[y - start[Y]][x - start[X]] = get_ray(data, job, x, y);
			x++;
		}
		y++;
	}
	return (true);
}
