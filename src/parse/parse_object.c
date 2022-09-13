/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 19:20:49 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/13 14:53:34 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <parse.h>
#include <libft.h>

// static bool	get_light(char *line, t_object *object);
// static bool	get_sphere(char *line, t_object *object);
// static bool	get_plane(char *line, t_object *object);
// static bool	get_cylinder(char *line, t_object *object);

static bool	get_camera(char *line, t_object *object)
{
	object->type = CAMERA;
	return (true);
}

static bool	get_ambient(char *line, t_object *object)
{
	object->type = AMBIENT;
	object->ambient.ratio = ft_strtof(line, &line);
	if (*line != ' ' || object->ambient.ratio < 0.0 || \
		object->ambient.ratio > 1.0)
		return (parse_line_error(line, LRATIO));
	if (!parse_rgb(line, &object->ambient.colour))
		return (parse_line_error(line, COLOUR));
	return (true);
}

bool	parse_object(char *line, t_object *object)
{
	if (ft_strncmp(line, "A ", 2) == 0)
		return (get_ambient(line + 1, object));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (get_camera(line + 1, object));
	// if (ft_strncmp(line, "L ", 2) == 0)
	// 	return (get_light(line + 1, object));
	// if (ft_strncmp(line, "sp ", 3) == 0)
	// 	return (get_sphere(line + 2, object));
	// if (ft_strncmp(line, "pl ", 3) == 0)
	// 	return (get_plane(line + 2, object));
	// if (ft_strncmp(line, "cy ", 3) == 0)
	// 	return (get_cylinder(line + 2, object));
	parse_line_error(line, OBJECT);
	return (false);
}
