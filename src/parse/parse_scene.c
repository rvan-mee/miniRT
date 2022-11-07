/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 02:00:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/07 21:20:39 by rvan-mee      ########   odam.nl         */
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

static bool	cleanup(char *line, t_conf_data *data)
{
	free(line);
	dynarr_delete(&data->lights);
	dynarr_delete(&data->objects);
	dynarr_delete(&data->vertices);
	dynarr_delete(&data->vertex_textures);
	dynarr_delete(&data->vertex_normals);
	return (false);
}

static bool	check_error(t_scene *dst, t_conf_data *data)
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
	store_object(t_object *obj, t_scene *dst, t_conf_data *conf)
{
	t_object	*store;

	store = NULL;
	if (obj->type == COMMENT || obj->type == LIGHT || obj->type == VERTEX \
		|| obj->type == VT_TEXTURE || obj->type == VT_NORMAL)
		return (true);
	if (obj->type == VT_TEXTURE)
		return (dynarr_addone(&conf->vertex_textures, &obj->vertex_texture));
	if (obj->type == VT_NORMAL)
		return (dynarr_addone(&conf->vertex_normals, &obj->vertex_normal));
	if (obj->type == CAMERA)
		store = &dst->camera;
	else if (obj->type == AMBIENT)
		store = &dst->ambient;
	else if (obj->type != UNINITIALIZED && obj->type != END)
		return (dynarr_addone(&conf->objects, obj));
	if (store != NULL && store->type != obj->type)
		return (*store = *obj, true);
	if (store != NULL)
		dprintf(STDERR_FILENO, DUPLICATE_ERROR, g_type_strs[obj->type]);
	else
		dprintf(STDERR_FILENO, UNKNOWN_ERROR, g_type_strs[obj->type]);
	return (false);
}

static bool \
	read_objects(int32_t fd, t_scene *dst, t_conf_data *conf)
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
			if (!parse_object(line, &object, conf) || \
				!store_object(&object, dst, conf))
				return (cleanup(line, conf));
		free(line);
	}
	return (check_error(dst, conf));
}

bool	parse_scene(int32_t fd, t_scene *dst)
{
	t_conf_data		parse_data;
	const size_t	vt_size = sizeof(t_vertex_texture);

	ft_bzero(dst, sizeof(t_scene));
	ft_bzero(&parse_data, sizeof(t_conf_data));
	if (!dynarr_create(&parse_data.lights, 4, sizeof(t_light)) || \
		!dynarr_create(&parse_data.objects, 16, sizeof(t_object)) || \
		!dynarr_create(&parse_data.vertices, 256, sizeof(t_vertex)) || \
		!dynarr_create(&parse_data.vertex_normals, 256, sizeof(t_normals)) || \
		!dynarr_create(&parse_data.vertex_textures, 256, vt_size))
		return (cleanup(NULL, &parse_data));
	if (!read_objects(fd, dst, &parse_data))
		return (false);
	dst->lights = parse_data.lights.arr;
	dst->lights_len = parse_data.lights.length;
	dst->objects = parse_data.objects.arr;
	dst->objects_len = parse_data.objects.length;
	dynarr_delete(&parse_data.vertex_textures);
	dynarr_delete(&parse_data.vertex_normals);
	dynarr_delete(&parse_data.vertices);
	return (true);
}
