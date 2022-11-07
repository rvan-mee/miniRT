/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aabb_intersect.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:00:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/01 15:00:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <render.h>
#include <math.h>

static inline
bool	contains(const t_aabb bounds, const t_fvec point)
{
	return (bounds.min[X] <= point[X] && bounds.max[X] >= point[X] && \
			bounds.min[Y] <= point[Y] && bounds.max[Y] >= point[Y] && \
			bounds.min[Z] <= point[Z] && bounds.max[Z] >= point[Z]);
}

float	aabb_intersect(const t_aabb bounds, const t_ray *ray)
{
	t_aabb	minmax;
	t_fvec	t[2];
	float	tlims[2];

	if (contains(bounds, ray->origin))
		return (0);
	t[0] = (bounds.min - ray->origin) / ray->direction;
	t[1] = (bounds.max - ray->origin) / ray->direction;
	minmax = (t_aabb){
		.min = (t_fvec){
			fminf(t[0][X], t[1][X]),
			fminf(t[0][Y], t[1][Y]),
			fminf(t[0][Z], t[1][Z])},
		.max = (t_fvec){
			fmaxf(t[0][X], t[1][X]),
			fmaxf(t[0][Y], t[1][Y]),
			fmaxf(t[0][Z], t[1][Z])}
	};
	tlims[0] = fmaxf(fmaxf(minmax.min[X], minmax.min[Y]), minmax.min[Z]);
	tlims[1] = fminf(fminf(minmax.max[X], minmax.max[Y]), minmax.max[Z]);
	if (tlims[0] > tlims[1])
		return (MISS);
	return (tlims[0]);
}
