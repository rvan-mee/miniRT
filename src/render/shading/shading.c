/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shading.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 14:45:10 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/28 21:55:39 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <render.h>
#include <ft_math.h>
#include <texture.h>
#include <float.h>

#define MAX_REFLECTION_DEPTH	16

t_fvec	get_obj_rgba(t_object *object, t_hit *hit)
{
	static t_fvec	(*get_col_arr[])(t_object *, t_hit *) = {\
		[SPHERE] = get_sphere_hit_colour,	\
		[PLANE] = get_plane_hit_colour,		\
		[CYLINDER] = get_cyl_hit_colour,	\
		[TRIANGLE] = get_tri_hit_colour,	\
		[FACE] = get_face_hit_colour,		\
	};
	
	return (get_col_arr[object->type](object, hit));
}

static t_fvec	reflect_ray(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth)
{
	t_hit	r_hit;
	t_fvec	colour;

	colour = (t_fvec) {};
	r_hit.ray.origin = hit->hit;
	r_hit.ray.direction = reflect(hit->ray.direction, hit->normal);
	if (!intersect_bvh(&scene->bvh, &r_hit.ray, &r_hit))
		return (colour);
	r_hit.hit = r_hit.ray.origin + r_hit.ray.direction * r_hit.distance;
	calculate_normal(&r_hit);
	r_hit.hit -= r_hit.ray.direction * (1 - 128 * (FLT_EPSILON));
	colour = get_hit_colour(scene, r_hit.object, &r_hit, depth + 1);
	return (colour * object->mat->specular);
}

static t_fvec	get_ambient(t_scene *scene, t_fvec ka)
{
	t_fvec	colour;

	colour = scene->ambient.colour * scene->ambient.ambient.ratio;
	return (colour * ka);
}

static t_fvec	use_material(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth)
{
	t_fvec	colour;
	t_phong	p_args;

	p_args = (t_phong){
		.cam_hit = hit,
		.kd = object->mat->diffuse,
		.ks = object->mat->specular,
		.ns = object->mat->reflec
	};
	colour = get_ambient(scene, object->mat->ambient);
	colour += phong(scene, p_args);
	if (object->mat->illum == 3 && depth < MAX_REFLECTION_DEPTH)
		colour += reflect_ray(scene, object, hit, depth);
	return (colour);
}

t_fvec	get_hit_colour(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth)
{
	t_phong			p_args;
	t_fvec			colour;

	if (object->has_mat)
		return (use_material(scene, object, hit, depth));
	p_args = (t_phong){
		.cam_hit = hit, .kd = object->colour, .ks = (t_fvec){0.04f, 0.04f, 0.04f}, .ns = 1
	};
	colour = get_ambient(scene, object->colour);
	colour += phong(scene, p_args);
	return (colour);
}
