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

//TODO: Precalculate a lot off this stuff
// Radius squared
// Top cap mid vector
static bool	check_height(float tee, t_ray *ray, const t_cylinder *cyl)
{
	float	hit_proj[2];
	t_fvec	hit = ray->origin + ray->direction * tee;
	t_fvec	cyl_top = cyl->height * cyl->orientation;

	hit_proj[0] = dot_product(hit - cyl->coords, cyl_top);
	if (hit_proj[0] < 0)
		return (false);
	hit_proj[1] = dot_product(cyl_top, cyl_top);
	return (hit_proj[0] <= hit_proj[1]);
}

static uint8_t	intersect_inf_cyl(const t_cylinder *cyl, t_ray *ray, float t[2])
{
	t_quadratic	quad;
	t_fvec		p[2];
	float		temp;

	p[0] = cross_product(ray->origin - cyl->coords, cyl->orientation);
	p[1] = cross_product(ray->direction, cyl->orientation);
	quad.a = dot_product(p[1], p[1]);
	quad.b = dot_product(p[0], p[1]) * 2.0f;
	quad.c = dot_product(p[0], p[0]) - powf(cyl->diameter / 2, 2.0f);
	if (!solve_quadratic(&quad, t))
		return (0);
	if (t[0] == t[1])
		return (1);
	if (t[0] > t[1])
	{
		temp = t[1];
		t[1] = t[0];
		t[0] = temp;
	}
	return (2);
}

static float	intersect_tops(const t_cylinder *cyl, t_ray *ray, float angle_diff)
{
	const float	radius_squared = powf(cyl->diameter / 2, 2);
	t_fvec		top_mid;
	t_fvec		hit;
	float		dist[2];

	top_mid = cyl->coords - ray->origin;
	dist[0] = dot_product(top_mid, cyl->orientation) / angle_diff;
	hit = ray->origin + ray->direction * dist[0];
	hit -= top_mid;
	if (dot_product(hit, hit) > radius_squared)
		dist[0] = MISS;
	top_mid = cyl->coords + cyl->orientation * cyl->height;
	top_mid -= ray->origin;
	dist[1] = dot_product(top_mid, cyl->orientation) / angle_diff;
	hit = ray->origin + ray->direction * dist[1];
	hit -= top_mid;
	if (dot_product(hit, hit) > radius_squared)
		dist[1] = MISS;
	if (dist[0] < dist[1] && dist[0] >= 0)
		return (dist[0]);
	if (dist[1] < dist[0] && dist[1] >= 0)
		return (dist[1]);
	return (MISS);
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
	const float			angle_diff = dot_product(cyl->orientation, ray->direction);
	float				t[2];

	if (angle_diff == 1.0f)
		return (intersect_tops(cyl, ray, angle_diff));
	else if (intersect_inf_cyl(cyl, ray, t))
	{
		if (t[0] > 0 && check_height(t[0], ray, cyl))
			return (fminf(intersect_tops(cyl, ray, angle_diff), t[0]));
		if (t[1] > 0 && check_height(t[1], ray, cyl))
			return (fminf(intersect_tops(cyl, ray, angle_diff), t[1]));
	}
	if (angle_diff == 0.0f)
		return (MISS);
	return (intersect_tops(cyl, ray, angle_diff));
}
