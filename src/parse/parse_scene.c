/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 02:00:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/27 12:15:20 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <get_next_line.h>
#include <errno.h>
#include <unistd.h>

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
	[MTL] = "material",					\
	[END] = "end",
};

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
		|| obj->type == VT_TEXTURE || obj->type == VT_NORMAL \
		|| obj->type == MTL || obj->type == USEMTL)
		return (true);
	if (obj->type == EXPOSURE)
		return (dst->camera.camera.exposure = conf->exposure, true);
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
		conf->curr_line++;
		object = (t_object){};
		if (*line != '\n' && *line != '\0')
			if (!parse_object(line, &object, conf) || \
				!store_object(&object, dst, conf))
				return (cleanup_parse(line, conf));
		free(line);
	}
	return (check_error(dst, conf));
}

bool	parse_scene(int32_t fd, t_scene *dst)
{
	t_conf_data		data;

	init_parse(&data, fd);
	if (!read_objects(fd, dst, &data))
		return (false);
	set_scene(dst, &data);
	return (true);
}
