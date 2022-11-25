/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shading.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 14:45:10 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 14:40:54 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <render.h>
#include <ft_math.h>
#include <texture.h>

static t_rgba	get_obj_rgba(t_object *object, t_hit *hit)
{
	static t_rgba	(*get_col_arr[])(t_object *, t_hit *) = {\
		[SPHERE] = get_sphere_hit_colour,	\
		[PLANE] = get_plane_hit_colour,		\
		[CYLINDER] = get_cyl_hit_colour,	\
		[TRIANGLE] = get_tri_hit_colour,	\
		[FACE] = get_face_hit_colour,		\
	};
	
	return (get_col_arr[object->type](object, hit));
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
	t_ray			ray;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	(void) data;
	ray.origin = hit->hit;
	while (i < scene->lights_len)
	{
		light_hits = false;
		ray.direction = ray.origin - lights[i].coords;
		distance_to_light = dot_product(ray.direction, ray.direction);
		ray.direction = normalize_vector(ray.direction);
		facing_ratio = dot_product(ray.direction, hit->normal);
		if (facing_ratio <= 0)
		{
			i++;
			light_hits = true;
			continue ;
		}
		if (USE_BVH)
		{
			t_hit	shade_hit;

			shade_hit.ray = ray;
			if (intersect_bvh(&scene->bvh, &ray, &shade_hit) && shade_hit.distance * shade_hit.distance < distance_to_light)
			{
				light_hits = true;
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
		return (set_shade_colour(get_obj_rgba(object, hit), facing_ratio));
	return (0x00000FF);
}
