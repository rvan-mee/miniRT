/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shading.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 14:45:10 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/26 18:23:24 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <render.h>
#include <ft_math.h>

static t_rgba	get_obj_rgba(t_object *object)
{
	t_rgba	rgb;

	rgb.rgba = 0;
	if (object->type == SPHERE)
		return (object->sphere.colour);
	if (object->type == PLANE)
		return (object->plane.colour);
	if (object->type == CYLINDER)
		return (object->cylinder.colour);
	return (rgb);
}

// t_fvec	normalize_vector(t_fvec vec)
// {
// 	const float	mag = dot_product(vec, vec);
// 	t_fvec		norm;

// 	norm[X] = vec[X] / mag;
// 	norm[Y] = vec[Y] / mag;
// 	norm[Z] = vec[Z] / mag;
// 	return (norm);
// }

float	dist_between_vecs(t_fvec a, t_fvec b)
{
	return (sqrt(dot_product(a, b)));
}

uint32_t	change_rgb(t_rgba colour, int8_t p)
{
	return ((colour.r * (255 / p) << 24) + (colour.g * (255 / p) << 16) + (colour.b * (255 / p) << 8) + 255);
}

void	test(void)
{
}

uint32_t	get_hit_colour(t_scene *scene, t_object *object, t_hit *hit)
{
	const t_light	*lights = scene->lights;
	bool			has_angle;
	float			distance;
	float			distance_to_light;
	t_rgba			colour = get_obj_rgba(object);
	float			facing_ratio;
	t_ray			ray;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	ray.origin = hit->hit;
	if (hit->screen_x == 1345 && hit->screen_y == 608)
		test();
	while (i < scene->lights_len)
	{
		has_angle = false;
		ray.direction = lights[i].coords;
		distance_to_light = dist_between_vecs(ray.origin, lights[i].coords);
		ray.direction = normalize_vector(ray.direction - ray.origin);
		facing_ratio = dot_product(ray.direction, hit->normal);
		if (facing_ratio < 0 || facing_ratio > 1)
		{
			i++;
			continue ;
		}
		while (j < scene->objects_len)
		{
			distance = intersect(&scene->objects[j], &ray);
			if ((distance != MISS && distance < distance_to_light) && distance > 0)
			{
				has_angle = true;
				break ;
			}
			j++;
		}
		i++;
	}
	if (!has_angle)
		return (colour.rgba);
	return (0xFF000000);
}
