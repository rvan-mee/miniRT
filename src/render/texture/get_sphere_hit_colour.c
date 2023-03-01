/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_sphere_hit_colour.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 15:40:35 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 14:40:03 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <texture.h>
#include <math.h>
#include <ft_math.h>

t_rgba	get_texture_colour_sphere(t_hit *hit, t_mtl *texture)
{
	t_fvec	d;
	float	u;
	float	v;

	d[X] = hit->object->coords[X] - hit->hit[X];
	d[Y] = hit->object->coords[Y] - hit->hit[Y];
	d[Z] = hit->object->coords[Z] - hit->hit[Z];
	d = normalize_vector(d);
	u = 0.5f + atan2f(d[X], d[Z]) / (float) (2 * M_PI) * -1;
	v = 0.5f + asinf(d[Y]) / (float) M_PI;
	return (get_uv_colour(&texture->map_Kd, u, v));
}

t_rgba	get_sphere_hit_colour(t_object *object, t_hit *hit)
{
	if (object->has_mat && object->mat->is_enabled.map_Kd)
		return (get_texture_colour_sphere(hit, object->mat));
	return (object->colour);
}
