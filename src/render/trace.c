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

#include <render.h>
#include <float.h>

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

bool	trace(t_scene *scene, t_ray *ray, t_hit *hit)
{
	hit->distance = FLT_MAX;
	if ((USE_BVH && !intersect_bvh(&scene->bvh, ray, hit)) || \
		(!USE_BVH && !intersect_old(scene, ray, hit)))
		return (false);
	hit->hit = hit->ray.origin + hit->ray.direction * hit->distance;
	calculate_normal(hit);
	return (true);
}
