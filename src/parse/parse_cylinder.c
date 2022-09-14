/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:10:11 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/14 17:27:51 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <parse.h>
#include <libft.h>

t_parse_error	parse_cylinder(char **linep, t_object *object)
{
	char	*line;

	line = *linep;
	if (!parse_vector(&line, &object->cylinder.coords, false) \
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_vector(&line, &object->cylinder.orientation, true) \
		|| !ft_isspace(*line))
		return (VECTOR);
	object->cylinder.diameter = ft_strtof(line, &line);
	if (!ft_isspace(*line))
		return (DIAMETER);
	object->cylinder.height = ft_strtof(line, &line);
	if (!ft_isspace(*line))
		return (OBJ_HEIGHT);
	if (!parse_rgb(&line, &object->cylinder.colour) || \
		!(ft_isspace(*line) || *line == '\0'))
		return (COLOUR);
	*linep = line;
	return (SUCCESS);
}
