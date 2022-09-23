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

#include <ft_math.h>
#include <render.h>

static void swap(float *a, float *b)
{
	float c = *a;
	*a = *b;
	*b = c;
}

static bool	check_height(float tee, t_ray *ray, const t_cylinder *cyl)
{
	t_fvec hit = ray->origin + ray->direction * tee;
	t_fvec n_height = cyl->height * cyl->orientation;
	return (dot_product(hit - cyl->coords, n_height) > 0
		&& dot_product(hit - n_height, n_height) < 0);
}

/*
 * To find if we intersect the side of the actual cylinder we can use the
 * line-point distance formula (|| (P - a) x D ||) / || D ||
 * We can substitute the P with the ray formula (O + tV), and use the axis of
 * the cylinder as the line we're calculating the distance to. When this
 * distance is equal to the radius of the cylinder we are at an intersection
 * with the (infinitely high) cylinder.
 *
 * P0 = (Dx(O-a))
 * P1 = (DxV)
 *
 * t^2 * |P1|^2 + 2tP0.P1 + |P0|^2 - r^2|D|^2 = 0
 */
float	intersect_cylinder(t_object *object, t_ray *ray)
{
	// TODO: Norminette, optimization(?), end caps, names
	const t_cylinder	*cyl = &object->cylinder;
	t_quadratic			quad;
	t_fvec				p[2];
	float				t[2];

	p[0] = cross_product(ray->origin - cyl->coords, cyl->orientation);
	p[1] = cross_product(ray->direction, cyl->orientation);
	quad.a = dot_product(p[1], p[1]);
	quad.b = dot_product(p[0], p[1]) * 2.0f;
	quad.c = dot_product(p[0], p[0]);
	quad.c -= dot_product(cyl->orientation, cyl->orientation) * powf(cyl->diameter / 2, 2.0f);
	if (solve_quadratic(&quad, t))
	{
		if (t[0] > t[1])
			swap(t + 0, t + 1);
		if (t[0] > 0 && check_height(t[0], ray, cyl))
			return (t[0]);
		if (t[1] > 0 && check_height(t[1], ray, cyl))
			return (t[1]);
	}
	return (MISS);
}
