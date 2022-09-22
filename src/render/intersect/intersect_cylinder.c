/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_cylinder.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:35:26 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/22 14:35:26 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <ft_math.h>

#define A 0
#define B 1
#define C 2

static float	get_a(t_cylinder *cyl, t_ray *ray)
{
	const float		dir_diff = dot_product(cyl->orientation, ray->direction);
	const t_fvec	scaled_dir = dir_diff * cyl->orientation;
	const t_fvec	closest_whatever = ray->direction - scaled_dir;
	return (dot_product(closest_whatever, closest_whatever));
}

float	intersect_cylinder(t_object *object, t_ray *ray)
{
	float	quadratic[3];

	quadratic[A] = get_a(&object->cylinder, ray);

	return (0.0f);
}
