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

static t_fvec	get_ambient(t_scene *scene, t_fvec ka)
{
	t_fvec	colour;

	colour = scene->ambient.colour * scene->ambient.ambient.ratio;
	return (colour * ka);
}

static t_phong	init_struct(t_object *obj, t_hit *hit)
{
	t_mtl	*mat;
	t_phong	ret;

	mat = obj->mat;
	ret = (t_phong){
		.cam_hit = hit,
		.ka = mat->ambient,
		.kd = mat->diffuse,
		.ks = mat->specular,
		.ns = mat->reflec
	};
	if (is_flag(mat, DIFFUSE_MAP))
		ret.kd *= get_texture(obj, hit, &mat->diffuse_tex);
	if (is_flag(mat, SPECULAR_MAP))
		ret.ks *= get_texture(obj, hit, &mat->specular_tex);
	if (is_flag(mat, AMBIENT_MAP))
		ret.ka *= get_texture(obj, hit, &mat->ambient_tex);
	return (ret);
}

static
t_fvec	use_material(t_scene *scene, t_hit *hit, uint8_t depth)
{
	t_object	*object;
	t_mtl		*mat;
	t_fvec		colour;
	t_phong		p_args;

	object = hit->object;
	mat = object->mat;
	p_args = init_struct(hit->object, hit);
	colour = get_ambient(scene, p_args.ka);
	colour += phong(scene, p_args);
	if (is_flag(mat, REFRACT_IDX))
		colour += fresnel(scene, p_args.ks, hit, depth);
	else if (mat->illum == 3 && depth < MAX_REFLECTION_DEPTH)
		colour += reflect_ray(scene, hit, depth) * p_args.ks;
	if (is_flag(mat, EMMISIVE_C))
		colour += mat->emmis_col;
	return (colour);
}

t_fvec	shade(t_scene *scene, t_hit *hit, uint8_t depth)
{
	t_object		*object;
	t_phong			p_args;
	t_fvec			colour;

	object = hit->object;
	if (object->has_mat)
		return (use_material(scene, hit, depth));
	p_args = (t_phong){ // todo: also look at this!
		.cam_hit = hit,
		.kd = object->colour,
		.ks = (t_fvec){0.04f, 0.04f, 0.04f},
		.ns = 1
	};
	colour = get_ambient(scene, object->colour);
	colour += phong(scene, p_args);
	return (colour);
}
