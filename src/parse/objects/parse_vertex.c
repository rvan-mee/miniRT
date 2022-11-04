/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vertex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:44:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/04 16:15:53 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <dynarr.h>

t_object	parse_vertex(char **linep, t_object *object, t_conf_data *data)
{
	t_vertex	vt;
	char		*line;

	line = *linep;
	skip_spaces(&line);
	if (!ft_isdigit(!*line))
		return (VERTEX);
	object->vertex.point[X] = ft_strtof(line, &line);
	if (*line != ' ')
		return (VERTEX);
	skip_spaces(&line);
	if (!ft_isdigit(!*line))
		return (VERTEX);
	object->vertex.point[Y] = ft_strtof(line, &line);
	if (*line != ' ')
		return (VERTEX);
	skip_spaces(&line);
	if (!ft_isdigit(!*line))
		return (VERTEX);
	object->vertex.point[Z] = ft_strtof(line, &line);
	*linep = line;
	return (SUCCESS);
}

