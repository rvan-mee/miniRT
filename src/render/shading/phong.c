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

static t_fvec	phong_light(t_object *light, t_phong args)
{
	float	ratio;
	t_fvec	colour;
	t_fvec	light_r;

	colour = (t_fvec){};
	ratio = dot_product(args.shadow_ray.direction, args.cam_hit->normal);
	if (ratio <= 0)
		return (colour);
	colour += args.kd * light->colour * ratio * args.brightness;
	light_r = reflect(-args.shadow_ray.direction, args.cam_hit->normal);
	ratio = dot_product(light_r, -args.cam_hit->ray.direction);
	if (ratio <= 0)
		return (colour);
	colour += args.ks * light->colour * powf(ratio, args.ns) * args.brightness;
	return (colour);
}

t_fvec	phong(t_scene *scene, t_phong args)
{
	t_object	*light;
	size_t		i;
	t_hit		shadow_hit;
	t_fvec		colour;

	colour = (t_fvec){};
	i = 0;
	while (i < scene->lights_len)
	{
		shadow_hit = (t_hit){};
		light = scene->lights + i++;
		args.light_rel = light->coords - args.cam_hit->hit;
		args.light_dist_sq = dot_product(args.light_rel, args.light_rel);
		args.shadow_ray.direction = normalize_vector(args.light_rel);
		args.shadow_ray.origin = args.cam_hit->hit + args.shadow_ray.direction * 1e-3f;;
		if (dot_product(args.shadow_ray.direction, args.cam_hit->normal) < 0)
			continue;
		args.brightness = light->light.brightness / args.light_dist_sq;
		args.brightness *= scene->camera.camera.exposure;
		if (intersect_bvh(&scene->bvh, &args.shadow_ray, &shadow_hit)
			&& shadow_hit.distance * shadow_hit.distance < args.light_dist_sq)
			continue;
		colour += phong_light(light, args);
	}
	return (colour);
}
