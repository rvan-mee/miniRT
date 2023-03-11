/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_bounds.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/11 22:32:07 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/11 22:32:07 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <float.h>

#define DEBUG_MES	"calc_bounds called on object with no function?! %i\n"

static t_aabb	sphere_bounds(t_object *obj)
{
	return ((t_aabb){
		obj->coords - (obj->sphere.diameter / 2),
		obj->coords + (obj->sphere.diameter / 2)
	});
}

static t_aabb	inf_obj_bounds(t_object *obj)
{
	const float	half_flt_max = FLT_MAX / 2;

	(void) obj;
	return ((t_aabb){
		{-half_flt_max, -half_flt_max, -half_flt_max},
		{+half_flt_max, +half_flt_max, +half_flt_max}
	});
}

static t_aabb	cyl_bounds(t_object *obj)
{
	const t_aabb	bot = {
		obj->coords - (obj->cylinder.diameter / 2),
		obj->coords + (obj->cylinder.diameter / 2)
	};
	const t_aabb	top = {
		obj->coords + obj->cylinder.top - (obj->cylinder.diameter / 2),
		obj->coords + obj->cylinder.top + (obj->cylinder.diameter / 2)
	};

	return (aabb_combine(bot, top));
}

static t_aabb	triangle_bounds(t_object *obj)
{
	t_fvec	*vert;

	if (obj->type == TRIANGLE)
		vert = obj->triangle.vert;
	else
		vert = obj->face.vert;
	return ((t_aabb){
		.min = {
			fminf(fminf(vert[0][X], vert[1][X]), vert[2][X]),
			fminf(fminf(vert[0][Y], vert[1][Y]), vert[2][Y]),
			fminf(fminf(vert[0][Z], vert[1][Z]), vert[2][Z]),
		},
		.max = {
			fmaxf(fmaxf(vert[0][X], vert[1][X]), vert[2][X]),
			fmaxf(fmaxf(vert[0][Y], vert[1][Y]), vert[2][Y]),
			fmaxf(fmaxf(vert[0][Z], vert[1][Z]), vert[2][Z]),
		}
	});
}

t_aabb	calc_bounds(t_object *obj)
{
	static t_aabb	(*lut[END])(t_object *) = {\
		[SPHERE] = sphere_bounds,	\
		[PLANE] = inf_obj_bounds,	\
		[CYLINDER] = cyl_bounds,	\
		[FACE] = triangle_bounds,	\
		[TRIANGLE] = triangle_bounds
	};

	if (lut[obj->type])
		return (lut[obj->type](obj));
	else
	{
		dprintf(2, DEBUG_MES, obj->type);
		return (inf_obj_bounds(obj));
	}
}
