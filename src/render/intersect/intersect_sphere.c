/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_sphere.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:45:26 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/07 20:57:16 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <ft_math.h>

float	intersect_sphere(const t_object *object, const t_ray *ray, t_hit *hit)
{
	const t_sphere	*sphere = &object->sphere;
	const t_fvec	cam_to_sphere = ray->origin - object->coords;
	t_quadratic		quadratic;
	float			t[2];

	(void) hit;
	quadratic.a = dot_product(ray->direction, ray->direction);
	quadratic.b = dot_product(cam_to_sphere, ray->direction) * 2;
	quadratic.c = dot_product(cam_to_sphere, cam_to_sphere) - sphere->radius_sq;
	if (solve_quadratic(&quadratic, t) == false)
		return (MISS);
	if (t[0] > t[1] && t[1] > 0)
		t[0] = t[1];
	return (t[0]);
}
