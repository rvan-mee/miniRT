/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:30:32 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/07 21:13:26 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <dynarr.h>
# include <minirt.h>
# include <math.h>

# define MISS INFINITY

typedef	float	(*t_intersectfun)(const t_object *object, const t_ray *ray, t_hit *hit);

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

bool	intersect_bvh(const t_bvh *bvh, const t_ray *ray, t_hit *hit);
float	aabb_intersect(const t_aabb bounds, const t_ray *ray);
float	intersect(const t_object *object, const t_ray *ray, t_hit *hit);
float	intersect_plane(const t_object *object, const t_ray *ray, t_hit *hit);
float	intersect_cylinder(const t_object *object, const t_ray *ray, t_hit *hit);
float	intersect_sphere(const t_object *object, const t_ray *ray, t_hit *hit);
float	intersect_triangle(const t_object *object, const t_ray *ray, t_hit *hit);
float	intersect_face(const t_object *obj, const t_ray *ray, t_hit *hit);

void	calculate_normal(t_hit *hit);
t_ray	get_cam_ray(t_object *camera, size_t x, size_t y);

void	start_render(t_minirt *data, void *func_data);

#endif //RENDER_H
