/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 19:20:49 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/13 20:43:43 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <parse.h>
#include <libft.h>

static t_parse_error	parse_cylinder(char **linep, t_object *object)
{
	const char	*start_line = line;

	line += 2;
	object->type = CYLINDER;
	if (!is_space(*line))
		return (parse_line_error(start_line, OBJECT));
	if (!parse_vector(line, &line, &object->cylinder.coords, false) \
		|| !is_space(*line))
		return (parse_line_error(start_line, COORD));
	if (!parse_vector(line, &line, &object->cylinder.orientation, true) \
		|| !is_space(*line))
		return (parse_line_error(start_line, VECTOR));
	object->cylinder.diameter = ft_strtof(line, &line);
	if (!is_space(*line))
		return (parse_line_error(start_line, DIAMETER));
	object->cylinder.height = ft_strtof(line, &line);
	if (!is_space(*line))
		return (parse_line_error(start_line, OBJ_HEIGHT));
	if (!parse_rgb(line, &line, &object->cylinder.colour) \
		|| !is_space(*line))
		return (parse_line_error(start_line, COLOUR));
	if (!parse_line_end(line))
		return (parse_line_error(start_line, FORMAT));
	return (true);
}

static t_parse_error	parse_plane(char **linep, t_object *object)
{
	const char	*start_line = line;

	line += 2;
	object->type = PLANE;
	if (!is_space(*line))
		return (parse_line_error(start_line, OBJECT));
	if (!parse_vector(line, &line, &object->plane.coords, false) \
		|| !is_space(*line))
		return (parse_line_error(start_line, COORD));
	if (!parse_vector(line, &line, &object->plane.orientation, true) \
		|| !is_space(*line))
		return (parse_line_error(start_line, VECTOR));
	if (!parse_rgb(line, &line, &object->plane.colour))
		return (parse_line_error(start_line, COLOUR));
	if (!parse_line_end(line))
		return (parse_line_error(start_line, FORMAT));
	return (true);
}

static t_parse_error	parse_sphere(char **linep, t_object *object)
{
	const char	*start_line = line;

	line += 2;
	object->type = SPHERE;
	if (!is_space(*line))
		return (parse_line_error(start_line, OBJECT));
	if (!parse_vector(line, &line, &object->sphere.coords, false) \
		|| !is_space(*line))
		return (parse_line_error(start_line, COORD));
	object->sphere.diameter = ft_strtof(line, &line);
	if (!is_space(*line))
		return (parse_line_error(start_line, DIAMETER));
	if (!parse_rgb(line, &line, &object->sphere.colour))
		return (parse_line_error(start_line, COLOUR));
	if (!parse_line_end(line))
		return (parse_line_error(start_line, FORMAT));
	return (true);
}

static t_parse_error	parse_light(char **linep, t_object *object)
{
	const char	*start_line = line;

	line += 1;
	object->type = LIGHT;
	if (!is_space(*line))
		return (parse_line_error(start_line, OBJECT));
	if (!parse_vector(line, &line, &object->light.coords, false) \
		|| !is_space(*line))
		return (parse_line_error(start_line, COORD));
	object->light.brightness = ft_strtof(line, &line);
	if (!parse_float(object->light.brightness, 0.0f, 1.0f) \
		|| !is_space(*line))
		return (parse_line_error(start_line, BRIGHT));
	if (!parse_rgb(line, &line, &object->light.colour))
		return (parse_line_error(start_line, COLOUR));
	if (!parse_line_end(line))
		return (parse_line_error(start_line, FORMAT));
	return (true);
}

static t_parse_error	parse_camera(char **linep, t_object *object)
{
	const char	*start_line = line;

	line += 1;
	object->type = CAMERA;
	if (!is_space(*line))
		return (parse_line_error(start_line, OBJECT));
	if (!parse_vector(line, &line, &object->camera.coords, false) \
		|| !is_space(*line))
		return (parse_line_error(start_line, COORD));
	if (!parse_vector(line, &line, &object->camera.orientation, true) \
		|| !is_space(*line))
		return (parse_line_error(start_line, VECTOR));
	skip_spaces(line, &line);
	object->camera.fov = ft_atoi(line);
	if (object->camera.fov < 0 || object->camera.fov > 180)
		return (parse_line_error(start_line, FOV));
	while (*line && ft_isdigit(*line))
		line++;
	if (!parse_line_end(line))
		return (parse_line_error(start_line, FORMAT));
	return (true);
}

static t_parse_error	parse_ambient(char **linep, t_object *object)
{
	const char	*start_line = line;

	line += 1;
	object->type = AMBIENT;
	if (!is_space(*line))
		return (parse_line_error(start_line, OBJECT));
	object->ambient.ratio = ft_strtof(line, &line);
	if (!is_space(*line) || !parse_float(object->ambient.ratio, 0.0f, 1.0f))
		return (parse_line_error(start_line, LRATIO));
	if (!parse_rgb(line, &line, &object->ambient.colour))
		return (parse_line_error(start_line, COLOUR));
	if (!parse_line_end(line))
		return (parse_line_error(start_line, FORMAT));
	return (true);
}

static t_parse_error	(*g_parsefun[])(char **, t_object *) = {
	[AMBIENT] = parse_ambient,
	[CAMERA] = parse_camera,
	[LIGHT] = parse_light,
	[SPHERE] = parse_sphere,
	[PLANE] = parse_plane,
	[CYLINDER] = parse_cylinder,
};

static const char	*g_ids[] = {
	[AMBIENT] = "A",
	[CAMERA] = "C",
	[LIGHT] = "L",
	[SPHERE] = "sp",
	[PLANE] = "pl",
	[CYLINDER] = "cy",
};

bool	parse_object(char *line, t_object *object)
{
	const char		*start_line = line;
	t_obj_type		type;
	t_parse_error	err;
	size_t			id_len;
	
	type = UNINITIALIZED;
	while (++type != END)
	{
		id_len = ft_strlen(g_ids[type]);
		if (ft_strncmp(g_ids[type], line, id_len) == 0)
			break ;
	}
	line += id_len;
	if (type == END || !is_space(*line))
		return (parse_line_error(start_line, OBJECT));
	skip_spaces(&line);
	err = g_parsefun[type](&line, object);
	if (err != SUCCESS)
		return (parse_line_error(start_line, err));
	skip_spaces(&line);
	if (*line != '\0')
		return (parse_line_error(start_line, FORMAT));
	return (true);
}
