/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vertex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:44:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/13 17:05:08 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static bool	parse_num(char **linep, int32_t *coord)
{
	char	*line;
	size_t	i;

	line = *linep;
	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (i == 0)
		return (false);
	*coord = ft_atoi(line);
	*linep = &line[i];
	return (true);
}

t_object	parse_vertex(char **linep, t_object *object)
{
	static unsigned long	vt_index;
	t_vertex				*vt;
	char					*line;

	vt = &object->vertex;
	vt->index = vt_index;
	vt_index++;
	line = *linep;
	if (!parse_num(&line, &vt->point[X]) || *line++ != ',')
		return (COORD);
	if (!parse_num(&line, &vt->point[Y]) || *line++ != ',')
		return (COORD);
	if (!parse_num(&line, &vt->point[Z]))
		return (COORD);
	skip_spaces(&line);
	if (!*line)
	{
		*linep = line;
		vt->has_uv = false;
		return (SUCCESS);
	}
	vt->has_uv = true;
	if (!parse_float(&line, &vt->u, 0, 1)
		|| !ft_isspace(*line))
		return (UV);
	if (!parse_float(&line, &vt->v, 0, 1))
		return (UV);
	*linep= line;
	return (SUCCESS);
}

