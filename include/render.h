/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:30:32 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/12 13:43:24 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <dynarr.h>
# include <minirt.h>
# include <math.h>

# define MISS INFINITY

typedef struct s_tri_intersect
{
	t_fvec	tvec;
	t_fvec	qvec;
	float	inv_det;
	float	v;
	float	u;
	float	t;
}	t_tri_intersect;

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
float	intersect_triangle(t_object *obj, t_ray *ray);

void	calculate_normal(t_hit *hit);

#endif //RENDER_H
