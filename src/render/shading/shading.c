/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shading.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 14:45:10 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/23 17:55:31 by rvan-mee      ########   odam.nl         */
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
	if (object->type == TRIANGLE)
		return (object->triangle.colour);
	return (rgb);
}

uint32_t	set_shade_colour(t_rgba colour, float facing_ratio)
{
	t_rgba	col;

	col = colour;
	col.r = (uint8_t) ((float) col.r * facing_ratio);
	col.g = (uint8_t) ((float) col.g * facing_ratio);
	col.b = (uint8_t) ((float) col.b * facing_ratio);
	col.a = 0xFF;
	return (col.rgba);
}

uint32_t	get_hit_colour(t_scene *scene, t_object *object, t_hit *hit)
{
	const t_light	*lights = scene->lights;
	bool			light_hits;
	float			distance;
	float			distance_to_light;
	float			facing_ratio;
	t_fvec			ray_to_light;
	t_ray			ray;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	ray.origin = hit->hit;
	while (i < scene->lights_len)
	{
		light_hits = false;
		ray.direction = lights[i].coords;
		ray_to_light = ray.origin - lights[i].coords;
		distance_to_light = dot_product(ray_to_light, ray_to_light);
		ray.direction = normalize_vector(ray.direction - ray.origin);
		facing_ratio = fmaxf(dot_product(ray.direction, hit->normal), 0.0f);
		if (facing_ratio < 0 || facing_ratio > 1)
		{
			i++;
			continue ;
		}
		while (j < scene->objects_len)
		{
			distance = intersect(&scene->objects[j], &ray);
			if ((distance != MISS && distance * distance < distance_to_light) && distance > 0)
			{
				light_hits = true;
				break ;
			}
			j++;
		}
		i++;
	}
	if (!light_hits)
		return (set_shade_colour(get_obj_rgba(object), facing_ratio));
	return (0x00000FF);
}
