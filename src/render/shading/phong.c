/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phong.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 14:34:51 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/06 14:34:51 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <ft_math.h>
#define SHADOW_BRIGHTNESS_CUTOFF 0.001f

static
t_fvec	phong_light(t_object *light, t_fvec dir, t_phong args)
{
	const t_hit	*hit = args.cam_hit;
	float		ratio;
	t_fvec		colour;
	t_fvec		light_r;

	ratio = dot_product(dir, hit->normal);
	colour = args.kd * light->colour * ratio * args.brightness;
	light_r = reflect(-dir, hit->normal);
	ratio = dot_product(light_r, -hit->ray.direction);
	if (ratio <= 0)
		return (colour);
	colour += args.ks * light->colour * powf(ratio, args.ns) * args.brightness;
	return (colour);
}

static
t_fvec	in_shadow(t_scene *scene, t_object *light, t_phong cols)
{
	const t_hit		*hit = cols.cam_hit;
	const t_fvec	l_rel = light->coords - hit->hit;
	const float		dist_sq = dot_product(l_rel, l_rel);
	t_hit			s_hit;

	s_hit.ray.direction = normalize_vector(l_rel);
	cols.brightness = light->light.brightness * scene->scale / dist_sq;
	if (cols.brightness < SHADOW_BRIGHTNESS_CUTOFF
		|| dot_product(s_hit.ray.direction, hit->normal) < 0)
		return ((t_fvec){});
	s_hit.ray = get_biased_ray(hit->hit, s_hit.ray.direction, hit->normal);
	if (intersect_bvh(&scene->bvh, &s_hit.ray, &s_hit) && \
		dist_sq > s_hit.distance * s_hit.distance)
		return ((t_fvec){});
	return (phong_light(light, s_hit.ray.direction, cols));
}

t_fvec	phong(t_scene *scene, t_phong args)
{
	t_fvec	colour;
	size_t	i;

	colour = (t_fvec){};
	i = 0;
	while (i < scene->lights_len)
		colour += in_shadow(scene, scene->lights + i++, args);
	return (colour);
}
