/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vertex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:44:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/07 14:03:59 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_vertex(char **linep, t_object *object, t_conf_data *conf)
{
	char		*line;

	line = *linep;
	skip_spaces(&line);
	if (!ft_isdigit(*line) && *line != '-')
		return (VERT);
	object->vertex.point[X] = ft_strtof(line, &line);
	if (*line != ' ')
		return (VERT);
	skip_spaces(&line);
	if (!ft_isdigit(*line) && *line != '-')
		return (VERT);
	object->vertex.point[Y] = ft_strtof(line, &line);
	if (*line != ' ')
		return (VERT);
	skip_spaces(&line);
	if (!ft_isdigit(*line) && *line != '-')
		return (VERT);
	object->vertex.point[Z] = ft_strtof(line, &line);
	if (!dynarr_addone(&conf->vertices, &object->vertex))
		return (DYNARR);
	*linep = line;
	return (SUCCESS);
}
