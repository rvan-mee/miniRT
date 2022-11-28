/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:46:41 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/28 21:57:53 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <ft_math.h>
#include <render.h>
#include <math.h>
#include <float.h>
#include <bvh.h>

bool	trace(
		t_scene *scene,
		t_ray *ray,
		const size_t screen[2],
		t_dynarr *hits)
{
	// const float	d_offset = (1 - 128 * (FLT_EPSILON));
	float		hit_distance;
	t_hit		hit;
	size_t		i;

	hit = (t_hit){(*ray), FLT_MAX, {}, NULL, {}, screen[X], screen[Y], 0, 0};
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
			hit_distance = intersect(scene->objects + i, ray, &hit);
			if (hit_distance < 0 || hit_distance >= hit.distance)
				continue;
			hit.distance = hit_distance;
			hit.object = scene->objects + i;
		}
	}
	if (hit.distance == FLT_MAX)
		return (true);
	// hit.hit = hit.ray.origin + hit.ray.direction * (hit.distance * d_offset);
	hit.hit = hit.ray.origin + hit.ray.direction * hit.distance;
	calculate_normal(&hit);
	hit.hit += hit.normal * (FLT_EPSILON * 128);
	return (dynarr_addone(hits, &hit));
}
