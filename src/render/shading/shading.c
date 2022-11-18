/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shading.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 14:45:10 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/16 17:18:18 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <render.h>
#include <ft_math.h>
#include <texture.h>

#ifndef USE_BVH
# define USE_BVH	1
#endif

static t_rgba	get_obj_rgba(t_object *object)
{
	t_rgba	rgb;

	rgb.rgba = 0;
	if (object->type == SPHERE)
		return (object->colour);
	if (object->type == PLANE)
		return (object->colour);
	if (object->type == CYLINDER)
		return (object->colour);
	if (object->type == TRIANGLE)
		return (object->colour);
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

uint32_t	get_hit_colour(t_minirt *data, t_scene *scene, t_object *object, t_hit *hit)
{
	const t_object	*lights = scene->lights;
	bool			light_hits = 0;
	float			distance;
	float			distance_to_light;
	float			facing_ratio = 0;
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
		ray.direction = lights[i].coords; // TODO: make copy of lights and scene (if you reload too quickly it has already been free'd) or lock it with mutex/semaphore
		ray_to_light = ray.origin - lights[i].coords;
		distance_to_light = dot_product(ray_to_light, ray_to_light);
		ray.direction = normalize_vector(ray.direction - ray.origin);
		facing_ratio = fmaxf(dot_product(ray.direction, hit->normal), 0.0f);
		if (facing_ratio < 0 || facing_ratio > 1)
		{
			i++;
			continue ;
		}
		if (USE_BVH)
		{
			t_hit	shade_hit;

			if (intersect_bvh(&scene->bvh, &ray, &shade_hit) && shade_hit.distance < distance_to_light)
			{
				++i;
				continue;
			}
			break ;
		}
		else
		{
			while (j < scene->objects_len)
			{
				distance = intersect(&scene->objects[j], &ray, hit);
				if ((distance != MISS && distance * distance < distance_to_light) && distance > 0)
				{
					light_hits = true;
					break;
				}
				j++;
			}
		}
		i++;
	}
	if (!light_hits)
	{
		if (object->type == SPHERE)
			return (set_shade_colour(get_texture_colour_sphere(hit, &data->temp_texture), facing_ratio));
		else
			return (set_shade_colour(get_obj_rgba(object), facing_ratio));
	}
	return (0x00000FF);
}
