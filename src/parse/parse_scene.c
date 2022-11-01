/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 02:00:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/07 20:58:53 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <dynarr.h>
#include <get_next_line.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#define DUPLICATE_ERROR		"Error\nThere can only be one %s!\n"
#define UNKNOWN_ERROR		"Error\nUnknown type %s\n"
#define NOT_ENOUGH_ERROR	"Error\nThere can't be zero %ss!\n"

static const char	*g_type_strs[] = {\
	[UNINITIALIZED] = "uninitialized",	\
	[AMBIENT] = "ambient",				\
	[CAMERA] = "camera",				\
	[LIGHT] = "light",					\
	[SPHERE] = "sphere",				\
	[PLANE] = "plane",					\
	[CYLINDER] = "cylinder",			\
	[TRIANGLE] = "triangle",			\
	[COMMENT] = "comment",				\
	[VERTEX] = "vertex",				\
	[VT_TEXTURE] = "vertex texture",	\
	[END] = "end",
};

static bool	cleanup(char *line, t_parse_data *data)
{
	free(line);
	dynarr_delete(&data->lights);
	dynarr_delete(&data->objects);
	dynarr_delete(&data->vertices);
	return (false);
}

static bool	check_error(t_scene *dst, t_parse_data *data)
{
	if (errno != 0)
		perror("Error during parsing");
	else if (data->lights.length == 0)
		dprintf(STDERR_FILENO, NOT_ENOUGH_ERROR, "lights");
	else if (data->objects.length == 0)
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
	store_object(t_object *obj, t_scene *dst, t_parse_data *data)
{
	t_object	*store;

	store = NULL;
	if (obj->type == COMMENT)
		return (true);
	if (obj->type == LIGHT)
		return (dynarr_addone(&data->lights, &obj->light));
	if (obj->type == VERTEX)
		return (dynarr_addone(&data->vertices, &obj->vertex));
	if (obj->type == VT_TEXTURE)
		return (dynarr_addone(&data->vertex_textures, &obj->vertex));
	if (obj->type == CAMERA)
		store = &dst->camera;
	else if (obj->type == AMBIENT)
		store = &dst->ambient;
	else if (obj->type != UNINITIALIZED && obj->type != END)
		return (dynarr_addone(&data->objects, obj));
	if (store != NULL && store->type != obj->type)
		return (*store = *obj, true);
	if (store != NULL)
		dprintf(STDERR_FILENO, DUPLICATE_ERROR, g_type_strs[obj->type]);
	else
		dprintf(STDERR_FILENO, UNKNOWN_ERROR, g_type_strs[obj->type]);
	return (false);
}

static bool \
	read_objects(int32_t fd, t_scene *dst, t_parse_data *data)
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
				!store_object(&object, dst, data))
				return (cleanup(line, data));
		free(line);
	}
	return (check_error(dst, data));
}

bool	parse_scene(int32_t fd, t_scene *dst)
{
	t_parse_data	parse_data;

	ft_bzero(dst, sizeof(t_scene));
	ft_bzero(&parse_data, sizeof(t_parse_data));
	if (!dynarr_create(&parse_data.lights, 4, sizeof(t_light)) || \
		!dynarr_create(&parse_data.objects, 16, sizeof(t_object)) || \
		!dynarr_create(&parse_data.vertices, 256, sizeof(t_vertex)) || \
		!dynarr_create(&parse_data.vertex_textures, 256, sizeof(t_vertex_texture)))
		return (cleanup(NULL, &parse_data));
	if (!read_objects(fd, dst, &parse_data))
		return (false);
	dst->lights = parse_data.lights.arr;
	dst->lights_len = parse_data.lights.length;
	dst->objects = parse_data.objects.arr;
	dst->objects_len = parse_data.objects.length;
	return (true);
}
