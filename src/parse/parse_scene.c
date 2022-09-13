/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 02:00:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/13 14:37:32 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include "get_next_line.h"
#include "parse.h"

static bool	cleanup(char *line, t_dynarr *lights, t_dynarr *objects)
{
	free(line);
	dynarr_delete(lights);
	dynarr_delete(objects);
	return (false);
}

static bool \
	store_object(t_object *obj, t_scene *dst, t_dynarr *lights, t_dynarr *objs)
{
	t_object	*store;

	store = NULL;
	if (obj->type == LIGHT)
		return (dynarr_addone(lights, &obj->light));
	if (obj->type == CAMERA)
		store = &dst->camera;
	else if (obj->type == AMBIENT)
		store = &dst->ambient;
	else
		return (dynarr_addone(objs, obj));
	if (store != NULL && store->type != obj->type)
	{
		*store = *obj;
		return (true);
	}
	return (false);
	// Todo: bunch of error messages
}

static bool \
	read_objects(int32_t fd, t_scene *dst, t_dynarr *lights, t_dynarr *objects)
{
	char		*line;
	t_object	object;

	while (true)
	{
		// todo: think about if we should maybe use errno to check if gnl returned NULL because of an error
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line != '\n' && *line != '\0')
			if (!parse_object(line, &object) || \
				!store_object(&object, dst, lights, objects))
				return (cleanup(line, lights, objects));
		free(line);
	}
	if (lights->length > 0
		&& objects->length > 0
		&& dst->ambient.type == AMBIENT
		&& dst->camera.type == CAMERA
		&& dynarr_finalize(lights) && dynarr_finalize(objects))
		return (true);
	return (cleanup(NULL, lights, objects));
}

bool	parse_scene(int32_t fd, t_scene *dst)
{
	t_dynarr	lights;
	t_dynarr	objects;

	ft_bzero(dst, sizeof(t_scene));
	if (!dynarr_create(&lights, 4, sizeof(t_light)) || \
		!dynarr_create(&objects, 16, sizeof(t_object)))
		return (cleanup(NULL, &lights, &objects));
	if (!read_objects(fd, dst, &lights, &objects))
		return (false);
	dst->lights = lights.arr;
	dst->lights_len = lights.length;
	dst->objects = objects.arr;
	dst->objects_len = objects.length;
	return (true);
}
