/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:30:32 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/21 18:30:32 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <dynarr.h>
# include <minirt.h>

bool	cast_primary_rays(
		t_scene *scene,
		size_t width,
		size_t height,
		t_dynarr *hits);

bool	shade(
		t_scene *scene,
		t_dynarr *hits,
		uint32_t *pixels);

float	intersect(t_object *object, t_ray *ray);
float	intersect_plane(t_object *object, t_ray *ray);
float	intersect_cylinder(t_object *object, t_ray *ray);
float	intersect_sphere(t_object *object, t_ray *ray);

#endif //RENDER_H
