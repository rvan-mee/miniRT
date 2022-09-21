/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_coords.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 19:12:39 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/15 19:12:39 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	normalize_coords(t_scene *scene)
{
	const t_fvec	camera_coords = scene->camera.camera.coords;
	t_object		*cur;
	size_t			i;

	scene->camera.camera.coords -= camera_coords;
	i = 0;
	while (i < scene->lights_len)
		scene->lights[i++].coords -= camera_coords;
	i = 0;
	while (i < scene->objects_len)
	{
		cur = scene->objects + i++;
		if (cur->type == SPHERE)
			cur->sphere.coords -= camera_coords;
		else if (cur->type == PLANE)
			cur->plane.coords -= camera_coords;
		else if (cur->type == CYLINDER)
			cur->cylinder.coords -= camera_coords;
	}
}
