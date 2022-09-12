/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_objects.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 18:53:29 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 19:43:10 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <miniRT.h>
#include <dynarr.h>
#include <get_next_line.h>

static bool	init_scene(t_scene *scene)
{
	const int32_t	object_size = sizeof(t_object);

	scene->camera.type = UNINITIALIZED;
	scene->ambient.type = UNINITIALIZED;
	if (!dynarr_create(scene->lights, object_size * 16, object_size))
		return (false);
	if (!dynarr_create(scene->objects, object_size * 16, object_size))
	{
		dynarr_delete(scene->lights);
		return (false);
	}
	return (true);
}

bool	set_objects(int32_t fd, t_scene *scene)
{
	char		*line;
	t_object	object;

	if (init_scene(scene) == false)
		return (false);
	while (1)
	{
		line = get_next_line(fd);
		if (!*line)
			break ;
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		object = parse_object(line);
		free(line);
		if (object.type == ERROR || !add_object_to_scene(object, scene))  // add to scene
			return (false);
	}
	if (!scene_uninitialized()) // check uninitialized light / camera / ambient
		return (false);
	return (true);
}
