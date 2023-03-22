/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflect_ray.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 15:33:23 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/22 15:33:23 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <ft_math.h>

t_fvec	reflect_ray(t_scene *scene, t_hit *hit, uint8_t depth)
{
	t_hit	r_hit;
	t_fvec	r_dir;

	r_dir = reflect(hit->ray.direction, hit->normal);
	r_hit.ray = get_biased_ray(hit->hit, r_dir, hit->normal);
	if (!trace(scene, &r_hit.ray, &r_hit))
		return ((t_fvec){});
	return (shade(scene, &r_hit, depth + 1));
}
