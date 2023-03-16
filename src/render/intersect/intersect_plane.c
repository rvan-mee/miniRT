/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_plane.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 19:16:56 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/22 16:33:21 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <render.h>
#include <ft_math.h>
#include <math.h>

float	intersect_plane(const t_object *object, const t_ray *ray, t_hit *hit)
{
	const t_plane	*plane = &object->plane;
	float			perpendicularity;
	float			distance;
	t_fvec			diff;

	(void) hit;
	perpendicularity = dot_product(ray->direction, plane->orientation);
	if (fabsf(perpendicularity) < FLOAT_EPSILON)
		return (MISS);
	diff = object->coords - ray->origin;
	distance = dot_product(diff, plane->orientation) / perpendicularity;
	return (distance);
}
