#include <minirt.h>
#include <ft_math.h>

static void	sphere_normal(t_hit *hit)
{
	t_sphere	*s;

	s = &hit->object->sphere;
	hit->normal = normalize_vector(hit->hit - s->coords);
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
	bot_rel_hit = hit->hit - cyl->coords;
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

void	calculate_normal(t_hit *hit)
{
	static void	(*lut[])(t_hit *) = {
		[SPHERE] = sphere_normal,
		[PLANE] = plane_normal,
		[CYLINDER] = cylinder_normal,
	};
	lut[hit->object->type](hit);
	if (dot_product(hit->ray.direction, hit->normal) < 0)
		hit->normal = -hit->normal;
}
