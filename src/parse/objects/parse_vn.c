/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vn.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 17:04:06 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/06 18:43:34 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_vn(char **linep, t_object *object, t_conf_data *conf)
{
	char		*line;

	line = *linep;
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (COORD);
	object->vertex_normal.normal[X] = ft_strtof(line, &line);
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (COORD);
	object->vertex_normal.normal[Y] = ft_strtof(line, &line);
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (COORD);
	object->vertex_normal.normal[Z] = ft_strtof(line, &line);
	if (!dynarr_addone(&conf->vertex_normals, &object->vertex_normal))
		return (DYNARR);
	*linep = line;
	return (SUCCESS);
}
