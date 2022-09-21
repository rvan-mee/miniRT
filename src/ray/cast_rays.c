/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:46:41 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/21 15:46:41 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <ft_math.h>
#include <dynarr.h>
#include <math.h>
#include <float.h>

#define ASPECT_RATIO	0
#define PIXELS_WIDTH	1
#define PIXELS_HEIGHT	2

// TODO: Remove when able
float	intersect_plane(t_object *, t_ray *);
float	intersect_cylinder(t_object *, t_ray *);
float	intersect_sphere(t_object *, t_ray *);

static t_fvec	get_direction(
		const size_t screen[2],
		const size_t width,
		const size_t height,
		const float params[])
{
	t_fvec	coords;

	coords[X] = ((float) screen[X] + 0.5f) / (float) width;
	coords[Y] = ((float) screen[Y] + 0.5f) / (float) height;
	coords[X] = 1 - 2 * coords[X];
	coords[Y] = 1 - 2 * coords[Y];
	coords[X] *= params[PIXELS_WIDTH];
	coords[Y] *= params[PIXELS_HEIGHT];
	coords[Z] = 1;
	return (normalize_vector(coords));
}

static float	intersect(t_object *obj, t_ray *ray)
{
	static float	(*intersect_functions[])(t_object *, t_ray *) = {\
		[PLANE] = intersect_plane, \
		[CYLINDER] = intersect_cylinder, \
		[SPHERE] = intersect_sphere
	};

	return (intersect_functions[obj->type](obj, ray));
}

static bool	trace(t_scene *scene, t_ray *ray, size_t screen[2], t_dynarr *hits)
{
	size_t		i;
	t_hit		hit;
	float		hit_distance;

	hit = (t_hit){
		*ray, NULL, FLT_MAX, screen[X], screen[Y]
	};
	i = scene->objects_len;
	while (i--)
	{
		hit_distance = intersect(scene->objects + i, ray);
		if (hit_distance < 0 || hit_distance >= hit.distance)
			continue ;
		hit.distance = hit_distance;
		hit.object = scene->objects + i;
	}
	if (hit.distance == FLT_MAX)
		return (true);
	return (dynarr_addone(hits, &hit));
}

//TODO: Move canvas width/height to scene struct
// Maybe rename to cast_primary_rays?
bool	cast_rays(t_scene *scene, size_t width, size_t height, t_dynarr *hits)
{
	const float	params[] = {
		[ASPECT_RATIO] = (float) width / (float) height,
		[PIXELS_WIDTH] = tanf(scene->camera.camera.fov / 2),
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
			// so we're actually able to reuse it when acsting from other point
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
