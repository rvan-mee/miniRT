/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:18:22 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/14 17:18:22 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

t_parse_error	parse_camera(char **linep, t_object *object)
{
	char	*line;

	line = *linep;
	if (!parse_vector(&line, &object->camera.coords, false)
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_vector(&line, &object->camera.orientation, true)
		|| !ft_isspace(*line))
		return (VECTOR);
	object->camera.fov = ft_atoi(line);
	if (object->camera.fov < 0 || object->camera.fov > 180)
		return (FOV);
	skip_spaces(&line);
	if (*line == '+' || *line == '-')
		++line;
	while (*line && ft_isdigit(*line))
		line++;
	*linep = line;
	return (SUCCESS);
}
