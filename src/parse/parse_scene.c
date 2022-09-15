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

#include <parse.h>
#include <dynarr.h>
#include <get_next_line.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#define DUPLICATE_ERROR		"Error\nThere can only be one %s in the config file!\n"
#define UNKNOWN_ERROR		"Error\nUnknown type %s\n"
#define NOT_ENOUGH_ERROR	"Error\nThere can't be zero %s!\n"

static const char	*g_type_strs[] = {\
	[UNINITIALIZED] = "uninitialized",	\
	[AMBIENT] = "ambient",				\
	[CAMERA] = "camera",				\
	[LIGHT] = "light",					\
	[SPHERE] = "sphere",				\
	[PLANE] = "plane",					\
	[CYLINDER] = "cylinder",			\
	[END] = "end",
};

static bool	cleanup(char *line, t_dynarr *lights, t_dynarr *objects)
{
	free(line);
	dynarr_delete(lights);
	dynarr_delete(objects);
	return (false);
}

static bool	check_error(t_scene *dst, t_dynarr *lights, t_dynarr *objects)
{
	if (errno != 0)
		perror("Error during parsing");
	else if (lights->length == 0)
		dprintf(STDERR_FILENO, NOT_ENOUGH_ERROR, "lights");
	else if (objects->length == 0)
		dprintf(STDERR_FILENO, NOT_ENOUGH_ERROR, "objects");
	else if (dst->ambient.type != AMBIENT)
		dprintf(STDERR_FILENO, NOT_ENOUGH_ERROR, "ambient");
	else if (dst->camera.type != CAMERA)
		dprintf(STDERR_FILENO, NOT_ENOUGH_ERROR, "camera");
	else
		return (true);
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
	else if (obj->type != UNINITIALIZED && obj->type != END)
		return (dynarr_addone(objs, obj));
	if (store != NULL && store->type != obj->type)
	{
		*store = *obj;
		return (true);
	}
	if (store != NULL)
		dprintf(STDERR_FILENO, DUPLICATE_ERROR, g_type_strs[obj->type]);
	else
		dprintf(STDERR_FILENO, UNKNOWN_ERROR, g_type_strs[obj->type]);
	return (false);
}

static bool \
	read_objects(int32_t fd, t_scene *dst, t_dynarr *lights, t_dynarr *objects)
{
	char		*line;
	t_object	object;

	while (true)
	{
		errno = 0;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line != '\n' && *line != '\0')
			if (!parse_object(line, &object) || \
				!store_object(&object, dst, lights, objects))
				return (cleanup(line, lights, objects));
		free(line);
	}
	return (check_error(dst, lights, objects));
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
