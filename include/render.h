/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:30:32 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/22 19:00:02 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <dynarr.h>
# include <minirt.h>
# include <math.h>

# define MISS INFINITY

typedef	float	(*t_intersectfun)(const t_object *object, const t_ray *ray);

bool	cast_primary_rays(
			t_scene *scene,
			size_t width,
			size_t height,
			t_dynarr *hits);

bool	shade(
			t_scene *scene,
			t_dynarr *hits,
			uint32_t *pixels);

bool	intersect_bvh(const t_bvh *bvh, const t_ray *ray, t_hit *hit);
float	aabb_intersect(const t_aabb bounds, const t_ray *ray);
float	intersect(const t_object *object, const t_ray *ray);
float	intersect_plane(const t_object *object, const t_ray *ray);
float	intersect_cylinder(const t_object *object, const t_ray *ray);
float	intersect_sphere(const t_object *object, const t_ray *ray);

void	calculate_normal(t_hit *hit);

#endif //RENDER_H
