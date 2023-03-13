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

#include <minirt.h>
#include <ft_math.h>

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
	t_face		*face;
	t_triangle	*tr;

	if (hit->object->type == TRIANGLE)
	{
		tr = &hit->object->triangle;
		hit->normal = normalize_vector(cross_product(tr->v0v1, tr->v0v2));
	}
	else
	{
		face = &hit->object->face;
		if (USE_SMOOTH_SHADING && face->has_normal)
			hit->normal = hit->bary[0] * face->normals[0] + hit->bary[1] * face->normals[1] + hit->bary[2] * face->normals[2];
		else
			hit->normal = normalize_vector(cross_product(face->v0v1, face->v0v2));
	}
}

void	calculate_normal(t_hit *hit)
{
	static void	(*lut[])(t_hit *) = {
	[SPHERE] = sphere_normal,
	[PLANE] = plane_normal,
	[CYLINDER] = cylinder_normal,
	[TRIANGLE] = tr_f_normal,
	[FACE] = tr_f_normal,
	};

	lut[hit->object->type](hit);
	if (dot_product(hit->ray.direction, hit->normal) > 0)
		hit->normal = -hit->normal;
}
