/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_normal.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 13:54:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/03/13 15:58:32 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
#include <render.h>

static void	sphere_normal(t_hit *hit)
{
	hit->normal = normalize_vector(hit->hit - hit->object->coords);
}

static void	plane_normal(t_hit *hit)
{
	hit->normal = hit->object->plane.orientation;
}

static void	cylinder_normal(t_hit *hit)
{
	t_cylinder	*cyl;
	t_fvec		bot_rel_hit;
	t_fvec		top_rel_hit;
	float		hit_height;

	cyl = &hit->object->cylinder;
	bot_rel_hit = hit->hit - hit->object->coords;
	if (dot_product(bot_rel_hit, bot_rel_hit) < cyl->radius_sq)
	{
		hit->normal = -cyl->orientation;
		return ;
	}
	top_rel_hit = bot_rel_hit - cyl->top;
	if (dot_product(top_rel_hit, top_rel_hit) < cyl->radius_sq)
	{
		hit->normal = cyl->orientation;
		return ;
	}
	hit_height = dot_product(bot_rel_hit, cyl->orientation);
	hit->normal = normalize_vector(bot_rel_hit - cyl->orientation * hit_height);
}

static void	tr_f_normal(t_hit *hit)
{
	t_face		*fa;
	t_fvec		v0v1;
	t_fvec		v0v2;

	if (hit->object->type == TRIANGLE)
	{
		v0v1 = hit->object->triangle.v0v1;
		v0v2 = hit->object->triangle.v0v2;
	}
	else if (!USE_SMOOTH_SHADING || !hit->object->face.has_normal)
	{
		v0v1 = hit->object->face.v0v1;
		v0v2 = hit->object->face.v0v2;
	}
	else
	{
		fa = &hit->object->face;
		hit->normal = hit->bary[0] * fa->normals[0] \
					+ hit->bary[1] * fa->normals[1] \
					+ hit->bary[2] * fa->normals[2];
		return ;
	}
	hit->normal = normalize_vector(cross_product(v0v1, v0v2));
}

void	calculate_normal(t_hit *hit)
{
	const t_mtl	*mat = hit->object->mat;
	static void	(*lut[])(t_hit *) = {
	[SPHERE] = sphere_normal,
	[PLANE] = plane_normal,
	[CYLINDER] = cylinder_normal,
	[TRIANGLE] = tr_f_normal,
	[FACE] = tr_f_normal,
	};

	lut[hit->object->type](hit);
	if (dot_product(hit->ray.direction, hit->normal) > 0)
	{
		hit->normal = -hit->normal;
		if (hit->inside_ri == 1.0f && is_flag(mat, REFRACT_IDX)
			&& mat->illum != 4 && hit->object->type != PLANE)
			hit->inside_ri = mat->opt_dens;
	}
}
