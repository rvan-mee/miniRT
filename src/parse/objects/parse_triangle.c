/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_triangle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 17:10:24 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:54:59 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static void	pre_calc(t_triangle *tr)
{
	tr->v0v1 = tr->vert[1] - tr->vert[0];
	tr->v0v2 = tr->vert[2] - tr->vert[0];
}

t_parse_error	parse_triangle(char **linep, t_object *object)
{
	char	*line;

	line = *linep;
	if (!parse_vector(&line, &object->triangle.vert[0], false)
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_vector(&line, &object->triangle.vert[1], false)
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_vector(&line, &object->triangle.vert[2], false)
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_rgb(&line, &object->colour))
		return (COLOUR);
	pre_calc(&object->triangle);
	*linep = line;
	return (SUCCESS);
}
