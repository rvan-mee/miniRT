/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_cylinder.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:35:26 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/07 20:58:18 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
#include <render.h>

static bool	check_height(
		const t_object *obj,
		const t_cylinder *cyl,
		const t_ray *ray,
		float tee)
{
	const t_fvec	hit = ray->origin + ray->direction * tee;
	float			hit_height;

	hit_height = dot_product(hit - obj->coords, cyl->orientation);
	return (hit_height >= 0 && hit_height < cyl->height);
}

static uint8_t	intersect_inf_cyl(
		const t_object *obj,
		const t_cylinder *cyl,
		const t_ray *ray,
		float t[2])
{
	t_quadratic	quad;
	t_fvec		p[2];
	float		temp;

	p[0] = cross_product(ray->origin - obj->coords, cyl->orientation);
	p[1] = cross_product(ray->direction, cyl->orientation);
	quad.a = dot_product(p[1], p[1]);
	quad.b = dot_product(p[0], p[1]) * 2.0f;
	quad.c = dot_product(p[0], p[0]) - cyl->radius_sq;
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

static float	intersect_tops(
		const t_object *obj,
		const t_cylinder *cyl,
		const t_ray *ray,
		float angle_diff)
{
	t_fvec				rel_cap_mid;
	t_fvec				hit;
	float				dist[2];

	rel_cap_mid = obj->coords - ray->origin;
	dist[0] = dot_product(rel_cap_mid, cyl->orientation) / angle_diff;
	hit = ray->direction * dist[0] - rel_cap_mid;
	if (dist[0] < 0 || dot_product(hit, hit) > cyl->radius_sq)
		dist[0] = MISS;
	rel_cap_mid += cyl->top;
	dist[1] = dot_product(rel_cap_mid, cyl->orientation) / angle_diff;
	hit = ray->direction * dist[1] - rel_cap_mid;
	if (dist[1] < 0 || dot_product(hit, hit) > cyl->radius_sq)
		dist[1] = MISS;
	return (rt_minf(dist[0], dist[1]));
}

/*
 * To find if we intersect the side of the actual cylinder we can use the
 * line-point dist formula (|| (P - a) x D ||) / || D ||
 * We can substitute the P with the ray formula (O + tV), and use the axis of
 * the cylinder as the line we're calculating the dist to. When this
 * dist is equal to the radius of the cylinder we are at an intersection
 * with the (infinitely high) cylinder.
 *
 * P0 = (Dx(O-a))
 * P1 = (DxV)
 *
 * t^2 * |P1|^2 + 2tP0.P1 + |P0|^2 - r^2|D|^2 = 0
 */
float	intersect_cylinder(const t_object *obj, const t_ray *ray, t_hit *hit)
{
	const t_cylinder	*cyl = &obj->cylinder;
	float				angle_diff;
	float				t[2];

	(void) hit;
	angle_diff = dot_product(cyl->orientation, ray->direction);
	if (1.0f - rt_absf(angle_diff) < FLOAT_EPSILON)
		return (intersect_tops(obj, cyl, ray, angle_diff));
	else if (intersect_inf_cyl(obj, cyl, ray, t))
	{
		if (t[0] > 0 && check_height(obj, cyl, ray, t[0]))
			return (rt_minf(intersect_tops(obj, cyl, ray, angle_diff), t[0]));
		if (t[1] > 0 && check_height(obj, cyl, ray, t[1]))
			return (rt_minf(intersect_tops(obj, cyl, ray, angle_diff), t[1]));
	}
	return (intersect_tops(obj, cyl, ray, angle_diff));
}
