/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:30:32 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/26 21:32:47 by rvan-mee      ########   odam.nl         */
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

bool	trace(
		t_scene *scene,
		t_ray *ray,
		const size_t screen[2],
		t_dynarr *hits);

bool	cast_primary_rays(t_minirt *data, t_dynarr *hits, size_t y);

float	intersect(t_object *object, t_ray *ray);
float	intersect_plane(t_object *object, t_ray *ray);
float	intersect_cylinder(t_object *object, t_ray *ray);
float	intersect_sphere(t_object *object, t_ray *ray);
float	intersect_triangle(t_object *obj, t_ray *ray);

void	calculate_normal(t_hit *hit);

void	start_render(t_minirt *data, void *func_data);

#endif //RENDER_H
