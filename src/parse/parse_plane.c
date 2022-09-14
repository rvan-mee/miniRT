/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:12:53 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/14 17:28:39 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <parse.h>
#include <libft.h>

t_parse_error	parse_plane(char **linep, t_object *object)
{
	char	*line;

	line = *linep;
	if (!parse_vector(&line, &object->plane.coords, false) \
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_vector(&line, &object->plane.orientation, true) \
		|| !ft_isspace(*line))
		return (VECTOR);
	if (!parse_rgb(&line, &object->plane.colour))
		return (COLOUR);
	*linep = line;
	return (SUCCESS);
}
