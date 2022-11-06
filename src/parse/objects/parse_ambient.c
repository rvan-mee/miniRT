/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_ambient.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:18:21 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/06 15:34:28 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_ambient(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;

	line = *linep;
	(void) conf;
	if (!parse_float(&line, &object->ambient.ratio, 0.0f, 1.0f)
		|| !ft_isspace(*line))
		return (LRATIO);
	if (!parse_rgb(&line, &object->colour))
		return (COLOUR);
	*linep = line;
	return (SUCCESS);
}
