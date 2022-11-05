/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_primary_rays.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:46:41 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/22 19:09:26 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <ft_math.h>
#include <render.h>
#include <math.h>
#include <float.h>
#include <bvh.h>

#ifndef USE_BVH
# define USE_BVH		1
#endif

#define ASPECT_RATIO	0
#define PIXELS_WIDTH	1
#define PIXELS_HEIGHT	2

static t_fvec	get_direction(
		const size_t screen[2],
		const size_t width,
		const size_t height,
		const float params[])
{
	t_fvec	coords;

	coords[X] = ((float) screen[X] + 0.5f) / (float) width;
	coords[Y] = ((float) screen[Y] + 0.5f) / (float) height;
	coords[X] = 2 * coords[X] - 1;
	coords[Y] = 1 - 2 * coords[Y];
	coords[X] *= params[PIXELS_WIDTH];
	coords[Y] *= params[PIXELS_HEIGHT];
	coords[Z] = 1;
	return (normalize_vector(coords));
}

static bool	trace(
		t_scene *scene,
		t_ray *ray,
		const size_t screen[2],
		t_dynarr *hits)
{
	size_t		i;
	t_hit		hit;
	float		hit_distance;

	hit = (t_hit){*ray, FLT_MAX, {}, NULL, {}, screen[X], screen[Y]};
	if (USE_BVH)
	{
		if (!intersect_bvh(&scene->bvh, ray, &hit))
			return (true);
	}
	else
	{
		i = scene->objects_len;
		while (i--)
		{
			hit_distance = intersect(scene->objects + i, ray);
			if (hit_distance < 0 || hit_distance >= hit.distance)
				continue;
			hit.distance = hit_distance;
			hit.object = scene->objects + i;
		}
		if (hit.distance == FLT_MAX)
			return (true);
	}
	hit.hit = hit.ray.origin + hit.ray.direction * (hit.distance * (1 - 128 * FLT_EPSILON));
	calculate_normal(&hit);
	return (dynarr_addone(hits, &hit));
}

//TODO: Move canvas width/height to scene struct
bool	cast_primary_rays(
		t_scene *scene,
		size_t width,
		size_t height,
		t_dynarr *hits)
{
	const float	params[] = {\
		[ASPECT_RATIO] = (float) width / (float) height, \
		[PIXELS_WIDTH] = tanf(scene->camera.camera.fov / 2), \
		[PIXELS_HEIGHT] = params[PIXELS_WIDTH] / params[ASPECT_RATIO]
	};
	t_ray		ray;
	size_t		screen[2];

	screen[X] = 0;
	while (screen[X] < width)
	{
		screen[Y] = 0;
		while (screen[Y] < height)
		{
			//todo: everything below this should probably be a function
			// so we're actually able to reuse it when casting from other point
			// or trace should be a separate function? (not static)
			ray.origin = (t_fvec){0, 0, 0, 0};
			ray.direction = get_direction(screen, width, height, params);
			if (!trace(scene, &ray, screen, hits))
				return (false);
			++screen[Y];
		}
		++screen[X];
	}
	return (true);
}
