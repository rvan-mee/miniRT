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

static bool	parse_line_end(char *line)
{
	skip_spaces(line, &line);
	if (*line != '\n' && *line != '\0')
		return (false);
	return (true);
}

static bool	parse_cylinder(char *line, t_object *object)
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

static bool	parse_plane(char *line, t_object *object)
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

static bool	parse_sphere(char *line, t_object *object)
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

static bool	parse_light(char *line, t_object *object)
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

static bool	parse_camera(char *line, t_object *object)
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

static bool	parse_ambient(char *line, t_object *object)
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

bool	parse_object(char *line, t_object *object)
{
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_ambient(line, object));
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_camera(line, object));
	if (ft_strncmp(line, "L", 1) == 0)
		return (parse_light(line, object));
	if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_sphere(line, object));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_plane(line, object));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (parse_cylinder(line, object));
	parse_line_error(line, OBJECT);
	return (false);
}
