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

#include <parse.h>
#include <libft.h>

static bool	parse_fov(char **linep, uint8_t *dst)
{
	char	*line;
	int32_t	num;

	line = *linep;
	num = ft_atoi(line);
	if (num < 0 || num > 180)
		return (false);
	*dst = num;
	skip_spaces(&line);
	if (*line == '+' || *line == '-')
		++line;
	while (*line && ft_isdigit(*line))
		line++;
	*linep = line;
	return (true);
}

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
	if (!parse_fov(&line, &object->camera.fov))
		return (FOV);
	*linep = line;
	return (SUCCESS);
}
