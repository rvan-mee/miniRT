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
#include <render.h>
#include <float.h>
#include <bvh.h>

static bool	intersect_old(t_scene *scene, t_ray *ray, t_hit *hit)
{
	size_t	i;
	float	hit_distance;

	i = scene->objects_len;
	while (i--)
	{
		hit_distance = intersect(scene->objects + i, ray, hit);
		if (hit_distance < 0 || hit_distance >= hit->distance)
			continue;
		hit->distance = hit_distance;
		hit->object = scene->objects + i;
	}
	return (hit_distance != FLT_MAX);
}

bool	trace(
		t_scene *scene,
		t_ray *ray,
		const size_t screen[2],
		t_dynarr *hits)
{
	const float	d_offset = (1 - 128 * (FLT_EPSILON));
	t_hit		hit;

	hit = (t_hit){
		.ray = *ray,
		.distance = FLT_MAX,
		.screen_x = screen[X],
		.screen_y = screen[Y]
	};
	if (USE_BVH)
	{
		if (!intersect_bvh(&scene->bvh, ray, &hit))
			return (true);
	}
	else if (!intersect_old(scene, ray, &hit))
		return (true);
	hit.hit = hit.ray.origin + hit.ray.direction * hit.distance;
	calculate_normal(&hit);
	hit.hit -= hit.ray.direction * d_offset;
	return (dynarr_addone(hits, &hit));
}
