/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_uv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 15:40:35 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/07 21:11:07 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <texture.h>
#include <math.h>
#include <ft_math.h>

#define PI 3.141592653589793238

t_rgba	get_texture_colour_sphere(t_hit *hit, t_texture *texture)
{
	t_fvec	d;
	float	u;
	float	v;

	d[X] = hit->object->coords[X] - hit->hit[X];
	d[Y] = hit->object->coords[Y] - hit->hit[Y];
	d[Z] = hit->object->coords[Z] - hit->hit[Z];
	d = normalize_vector(d);
	u = 0.5 + atan2(d[X], d[Z]) / (2 * PI) * -1;
	v = 0.5 + asin(d[Y]) / PI;
	return (get_uv_colour(texture, u, v));
}
