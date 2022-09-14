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
	if (!parse_vector(line, &line, &object->cylinder.coords, false) \
		|| !is_space(*line))
		return (COORD);
	if (!parse_vector(line, &line, &object->cylinder.orientation, true) \
		|| !is_space(*line))
		return (VECTOR);
	object->cylinder.diameter = ft_strtof(line, &line);
	if (!is_space(*line))
		return (DIAMETER);
	object->cylinder.height = ft_strtof(line, &line);
	if (!is_space(*line))
		return (OBJ_HEIGHT);
	if (!parse_rgb(line, &line, &object->cylinder.colour) \
		|| !is_space(*line))
		return (COLOUR);
	*linep = line;
	return (SUCCESS);
}
