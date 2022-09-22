/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_plane.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 19:16:56 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/22 19:03:05 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <render.h>
#include <ft_math.h>
#include <float.h>
#include <math.h>

float	intersect_plane(t_object *object, t_ray *ray)
{
	t_plane	*plane;
	float	perpendicularity;
	float	distance;
	t_fvec	diff;

	plane = &object->plane;
	perpendicularity = dot_product(ray->direction, plane->orientation);
	if (perpendicularity < FLT_EPSILON * 128)
		return (MISS);
	diff = plane->coords - ray->origin;
	distance = dot_product(diff, plane->orientation) / perpendicularity;
	return (distance);
}
