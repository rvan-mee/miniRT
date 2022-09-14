/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_ambient.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:18:21 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/14 17:18:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_ambient(char **linep, t_object *object)
{
	char	*line;

	line = *linep;
	object->ambient.ratio = ft_strtof(line, &line);
	if (!is_space(*line) || !parse_float(object->ambient.ratio, 0.0f, 1.0f))
		return (LRATIO);
	if (!parse_rgb(&line, &object->ambient.colour))
		return (COLOUR);
	*linep = line;
	return (SUCCESS);
}
