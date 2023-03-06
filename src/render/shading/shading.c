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
#include <float.h>

#define MAX_REFLECTION_DEPTH	16

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

uint32_t	set_shade_colour(t_rgba colour, float facing_ratio, t_rgba ambient, float ambient_ratio)
{
	t_rgba	col;

	col = colour;
	col.r = (uint8_t) fminf(((float) col.r * facing_ratio) + ambient.r * ambient_ratio, 255.0f);
	col.g = (uint8_t) fminf(((float) col.g * facing_ratio) + ambient.g * ambient_ratio, 255.0f);
	col.b = (uint8_t) fminf(((float) col.b * facing_ratio) + ambient.b * ambient_ratio, 255.0f);
	col.a = 0xFF;
	return (col.rgba);
}

uint32_t	get_ambient_colour(t_rgba ambient, float ambient_ratio)
{
	t_rgba	col;

	col.r = ambient.r * ambient_ratio;
	col.g = ambient.g * ambient_ratio;
	col.b = ambient.b * ambient_ratio;
	col.a = 0xFF;
	return (col.rgba);
}

static t_fvec	rgb_to_vec(t_rgba rgb)
{
	return ((t_fvec) {
		(float) rgb.r / 255.f,
		(float) rgb.g / 255.f,
		(float) rgb.b / 255.f
	});
}

static t_fvec	reflect(t_fvec in, t_fvec normal)
{
	t_fvec	out;

	out = in - (2 * dot_product(normal, in) * normal);
	return (normalize_vector(out));
}

t_fvec	phong(t_scene *scene, t_fvec diff_col, t_fvec spec_col, float ns, t_hit *hit)
{
	size_t	i;
	t_hit	shadow;
	t_fvec	diffuse;
	t_fvec	specular;
	t_fvec	colour;

	colour = (t_fvec){};
	i = 0;
	while (i < scene->lights_len)
	{
		t_object *light = scene->lights + i++;
		t_ray ray;
		t_fvec light_rel = light->coords - ray.origin;
		ray.origin = hit->hit;
		ray.direction = normalize_vector(light_rel);
		if (intersect_bvh(&scene->bvh, &ray, &shadow))
			continue;
		float dif_ratio = dot_product(ray.direction, hit->normal);
		if (dif_ratio <= 0)
			continue;
		float brightness = light->light.brightness / dot_product(light_rel, light_rel);
		diffuse = diff_col * rgb_to_vec(light->colour) * dif_ratio * brightness;
		t_fvec r = reflect(ray.direction, hit->normal);
		float spec_ratio = powf(fmaxf(dot_product(r, -hit->ray.direction), 0), ns);
		specular = spec_col * rgb_to_vec(light->colour) * spec_ratio * brightness;
		colour += diffuse + specular;
	}
	return (colour);
}

uint32_t	get_hit_colour(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth);
t_fvec	reflect_ray(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth)
{
	t_hit	r_hit;
	t_fvec	colour;

	colour = (t_fvec) {};
	r_hit.ray = (t_ray) {
		hit->hit,
		reflect(hit->ray.direction, hit->normal)
	};
	if (!intersect_bvh(&scene->bvh, &r_hit.ray, &r_hit))
		return (colour);
	r_hit.hit = r_hit.ray.origin + r_hit.ray.direction * r_hit.distance;
	calculate_normal(&r_hit);
	r_hit.hit -= r_hit.ray.direction * (1 - 128 * (FLT_EPSILON));
	colour = rgb_to_vec((t_rgba) get_hit_colour(scene, r_hit.object, &r_hit, depth + 1));
	return (colour * object->mat->specular);
}

uint32_t	use_material(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth)
{
	t_rgba	rgba;
	t_fvec	colour;

	colour = rgb_to_vec(scene->ambient.colour) * scene->ambient.ambient.ratio;
	colour *= object->mat->ambient;
	colour += phong(scene, object->mat->diffuse, object->mat->specular, object->mat->reflec, hit);
	if (object->mat->illum == 3 && depth < MAX_REFLECTION_DEPTH)
		colour += reflect_ray(scene, object, hit, depth);
	rgba = (t_rgba){
		.r = (uint8_t) fminf(colour[0] * 255, 255.f),
		.g = (uint8_t) fminf(colour[1] * 255, 255.f),
		.b = (uint8_t) fminf(colour[2] * 255, 255.f),
		.a = 0xFF
	};
	return (rgba.rgba);
}

uint32_t	get_hit_colour(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth)
{
	const t_object	*lights = scene->lights;
	bool			light_hits = 0;
	float			distance;
	float			distance_to_light;
	float			facing_ratio = 0;
	t_ray			ray;
	size_t			i;
	size_t			j;

	if (object->has_mat)
		return (use_material(scene, object, hit, depth));
	i = 0;
	j = 0;
	ray.origin = hit->hit;
	while (i < scene->lights_len)
	{
		light_hits = false;
		ray.direction = lights[i].coords - ray.origin;
		distance_to_light = dot_product(ray.direction, ray.direction);
		ray.direction = normalize_vector(ray.direction);
		facing_ratio = dot_product(ray.direction, hit->normal);
		if (facing_ratio <= 0)
		{
			light_hits = true;
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
		return (set_shade_colour(get_obj_rgba(object, hit), facing_ratio, scene->ambient.colour, scene->ambient.ambient.ratio));
	return (get_ambient_colour(scene->ambient.colour, scene->ambient.ambient.ratio));
}
