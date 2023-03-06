/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_texture_sphere.c                            :+:    :+:            */
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

t_fvec	get_texture_sphere(t_hit *hit, t_bmp *texture)
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
	return (get_uv_colour(texture, u, v));
}
