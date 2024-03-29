/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scene_size.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 15:51:09 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/09 15:51:09 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <scene.h>
#include <float.h>
#include <math.h>
#include <ft_math.h>

void	get_scene_scale(t_scene *scene)
{
	const t_bvh		*bvh;
	const t_cluster	*cluster;
	t_fvec			delta;

	scene->scale = 1.0f;
	if (!USE_BVH)
		return ;
	bvh = &scene->bvh;
	cluster = bvh->clusters + bvh->root;
	while (true)
	{
		delta = cluster->aabb.max - cluster->aabb.min;
		if (delta[X] != FLT_MAX)
			break ;
		if (cluster->len == 1)
			return ;
		if (bvh->clusters[cluster->l].len > 1)
			cluster = bvh->clusters + cluster->l;
		else
			cluster = bvh->clusters + cluster->r;
	}
	scene->scale = rt_maxf(1, sqrtf(delta[X] * delta[X] + delta[Z] * delta[Z]));
}
