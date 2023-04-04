/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_face.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 18:55:43 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/22 16:30:28 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <ft_math.h>

// wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
float	intersect_face(const t_object *obj, const t_ray *ray, t_hit *hit)
{
	const t_face	*tr = &obj->face;
	const t_fvec	pvec = cross_product(ray->direction, tr->v0v2);
	const float		det = dot_product(tr->v0v1, pvec);
	t_tri_intersect	isect;

	isect.inv_det = 1.0f / det;
	isect.tvec = ray->origin - tr->vert[0];
	isect.u = dot_product(isect.tvec, pvec) * isect.inv_det;
	if (isect.u < 0.0f || isect.u > 1.0f)
		return (MISS);
	isect.qvec = cross_product(isect.tvec, tr->v0v1);
	isect.v = dot_product(ray->direction, isect.qvec) * isect.inv_det;
	if (isect.v < 0.0f || isect.u + isect.v > 1.0f)
		return (MISS);
	isect.t = dot_product(tr->v0v2, isect.qvec) * isect.inv_det;
	hit->bary = (t_fvec){1.0f - isect.u - isect.v, isect.u, isect.v};
	return (isect.t);
}
