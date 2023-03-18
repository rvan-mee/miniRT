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

static t_fvec	get_texture(t_object *object, t_hit *hit, t_bmp *texture)
{
	static t_fvec	(*get_col_arr[])(t_hit *, t_bmp *) = {\
		[SPHERE] = get_texture_sphere,		\
		[PLANE] = get_texture_plane,		\
		[CYLINDER] = get_texture_cyl,		\
		[TRIANGLE] = get_texture_triangle,	\
		[FACE] = get_texture_face
	};
	
	return (get_col_arr[object->type](hit, texture));
}

static t_fvec	reflect_ray(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth)
{
	t_hit	r_hit;
	t_fvec	colour;
	float	bias;

	colour = (t_fvec) {};
	r_hit.ray.direction = reflect(hit->ray.direction, hit->normal);
	bias = get_ray_bias(hit->normal, r_hit.ray.direction);
	r_hit.ray.origin = hit->hit + r_hit.ray.direction * bias;
	if (!intersect_bvh(&scene->bvh, &r_hit.ray, &r_hit))
		return (colour);
	r_hit.hit = r_hit.ray.origin + r_hit.ray.direction * r_hit.distance;
	calculate_normal(&r_hit);
	colour = shade(scene, r_hit.object, &r_hit, depth + 1);
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
	if (is_flag(object->mat, DIFFUSE_MAP))
		p_args.kd *= get_texture(object, hit, &object->mat->diffuse_tex);
	if (is_flag(object->mat, SPECULAR_MAP))
		p_args.ks *= get_texture(object, hit, &object->mat->specular_tex);
	colour = get_ambient(scene, object->mat->ambient);
	if (is_flag(object->mat, AMBIENT_MAP))
		colour *= get_texture(object, hit, &object->mat->ambient_tex);
	if (is_flag(object->mat, REFRACT_IDX))
		return (fresnel(scene, object, hit, depth));
	else
	{
		// todo: look at this
		colour += phong(scene, p_args);
		if (object->mat->illum == 3 && depth < MAX_REFLECTION_DEPTH)
			colour += reflect_ray(scene, object, hit, depth);
	}
	return (colour);
}

t_fvec	shade(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth)
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
