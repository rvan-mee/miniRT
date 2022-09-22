/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_sphere.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:45:26 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/22 15:57:32 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <ft_math.h>

float	intersect_sphere(t_object *obj, t_ray *ray)
{
	const float	rad2 = powf(obj->sphere.diameter / 2, 2);
	t_quadratic	quadratic;
	t_fvec		cam_to_sphere;
	float		t[2];

	cam_to_sphere = ray->origin - obj->sphere.coords;
	quadratic.a = dot_product(ray->direction, ray->direction);
	quadratic.b = dot_product(cam_to_sphere, ray->direction) * 2;
	quadratic.c = dot_product(cam_to_sphere, cam_to_sphere) - rad2;
	if (solve_quadratic(&quadratic, t) == false)
		return (MISS);
	if (t[0] > t[1] && t[1] > 0)
		t[0] = t[1];
	return (t[0]);
}
