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

bool	cast_primary_rays(
			t_scene *scene,
			size_t width,
			size_t height,
			t_dynarr *hits);

bool	shade(
			t_scene *scene,
			t_dynarr *hits,
			uint32_t *pixels);

bool	intersect_bvh(t_bvh *bvh, t_ray *ray, t_hit *hit);
float	aabb_intersect(t_aabb bounds, t_ray *ray);
float	intersect(t_object *object, t_ray *ray);
float	intersect_plane(t_object *object, t_ray *ray);
float	intersect_cylinder(t_object *object, t_ray *ray);
float	intersect_sphere(t_object *object, t_ray *ray);

void	calculate_normal(t_hit *hit);

#endif //RENDER_H
