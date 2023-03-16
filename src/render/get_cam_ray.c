/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cam_ray.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 00:14:26 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/02 00:14:26 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <ft_math.h>

t_ray	get_cam_ray(t_object *camera, size_t x, size_t y)
{
	const t_camera	*cam = &camera->camera;
	t_ray			ray;

	ray.origin = camera->coords;
	ray.direction = (cam->u * (float) x) +
					(-cam->v * (float) y) +
					(cam->proj_vec);
	ray.direction = normalize_vector(ray.direction);
	return (ray);
}
