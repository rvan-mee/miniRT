/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_coords.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 19:12:39 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/11 18:03:54 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	normalize_coords(t_scene *scene)
{
	const t_fvec	camera_coords = scene->camera.coords;
	t_object		*cur;
	size_t			i;

	scene->camera.coords -= camera_coords;
	i = 0;
	while (i < scene->lights_len)
		scene->lights[i++].coords -= camera_coords;
	i = 0;
	while (i < scene->objects_len)
	{
		cur = scene->objects + i++;
		if (cur->type == SPHERE || cur->type == PLANE ||cur->type == CYLINDER)
			cur->coords -= camera_coords;
		else if (cur->type == TRIANGLE)
		{
			cur->triangle.vert[0] -= camera_coords;
			cur->triangle.vert[1] -= camera_coords;
			cur->triangle.vert[2] -= camera_coords;
		}
	}
}
