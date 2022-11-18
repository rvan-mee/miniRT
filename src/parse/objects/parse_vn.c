/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vn.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 17:04:06 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 20:52:40 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_vn(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;
	char	*end;

	line = *linep;
	skip_spaces(&line);
	object->vertex_normal.normal[X] = ft_strtof(line, &end);
	skip_spaces(&line);
	if (line == end || !ft_isdigit(end[-1]))
		return (COORD);
	line = end;
	object->vertex_normal.normal[Y] = ft_strtof(line, &end);
	if (line == end || !ft_isdigit(end[-1]))
		return (COORD);
	line = end;
	skip_spaces(&line);
	object->vertex_normal.normal[Z] = ft_strtof(line, &end);
	if (line == end || !ft_isdigit(end[-1]))
		return (COORD);
	if (!dynarr_addone(&conf->vertex_normals, &object->vertex_normal))
		return (DYNARR);
	*linep = end;
	return (SUCCESS);
}
