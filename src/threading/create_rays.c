/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_rays.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:56:11 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/09 20:33:47 by rvan-mee      ########   odam.nl         */
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

static t_ray	get_ray(t_minirt *data, t_render *block, size_t x, size_t y)
{
	const float	params[] = {\
		[ASPECT_RATIO] = (float) data->width / (float) data->height, \
		[PIXELS_WIDTH] = tanf(block->camera.camera.fov / 2), \
		[PIXELS_HEIGHT] = params[PIXELS_WIDTH] / params[ASPECT_RATIO]
	};
	t_ray	ray;
	t_fvec	coords;

	ray.origin = block->camera.coords;
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

static bool	allocate_rays(t_render *block)
{
	size_t	i;

	i = 0;
	block->rays = ft_calloc(block->size[Y] + 1, sizeof(t_ray *));
	if (!block->rays)
		return (false);
	while (i < block->size[Y])
	{
		block->rays[i] = malloc(sizeof(t_ray) * (block->size[X] + 1));
		if (!block->rays[i])
			return (clean_rays(block->rays), false);
		i++;
	}
	return (true);
}

bool	create_rays(t_minirt *data, t_render *block)
{
	size_t	start[2];
	size_t	end[2];
	size_t	x;
	size_t	y;

	start[X] = block->start_pixels[X];
	start[Y] = block->start_pixels[Y];
	end[X] = block->end_pixels[X];
	end[Y] = block->end_pixels[Y];
	if (!allocate_rays(block))
		return (false);
	y = start[Y];
	while (y < end[Y])
	{
		x = start[X];
		while (x < end[X])
		{
			block->rays[y - start[Y]][x - start[X]] = get_ray(data, block, x, y);
			x++;
		}
		y++;
	}
	return (true);
}
