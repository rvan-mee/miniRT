/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vertex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:44:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/22 18:52:59 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

#include <stdlib.h>
#include <unistd.h>
t_parse_error	parse_vertex(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;
	char	*end;

	line = *linep;
	skip_spaces(&line);
	object->vertex.point[X] = strtof(line, &end); // TODO: change to ft_
	if (line == end || !ft_isdigit(end[-1]))
		return (VERT);
	line = end;
	skip_spaces(&line);
	object->vertex.point[Y] = strtof(line, &end);
	if (line == end || !ft_isdigit(end[-1]))
		return (VERT);
	line = end;
	skip_spaces(&line);
	object->vertex.point[Z] = strtof(line, &end);
	if (line == end || !ft_isdigit(end[-1]))
		return (VERT);
	if (!dynarr_addone(&conf->vertices, &object->vertex))
		return (DYNARR);
	*linep = end;
	return (SUCCESS);
}
