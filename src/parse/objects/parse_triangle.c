/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_triangle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 17:10:24 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/27 15:07:14 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static void	pre_calc(t_triangle *tr)
{
	tr->v0v1 = tr->vert[1] - tr->vert[0];
	tr->v0v2 = tr->vert[2] - tr->vert[0];
}
#include <math.h>
t_parse_error	parse_triangle(char **linep, \
								t_object *object, t_conf_data *conf)
{
	char	*line;

	line = *linep;
	(void) conf;
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
	object->coords[0] = (fminf(fminf(object->triangle.vert[0][X], object->triangle.vert[1][X]), object->triangle.vert[2][X]) + fmaxf(fmaxf(object->triangle.vert[0][X], object->triangle.vert[1][X]), object->triangle.vert[2][X])) / 2;
	object->coords[1] = (fminf(fminf(object->triangle.vert[0][Y], object->triangle.vert[1][Y]), object->triangle.vert[2][Y]) + fmaxf(fmaxf(object->triangle.vert[0][Y], object->triangle.vert[1][Y]), object->triangle.vert[2][Y])) / 2;
	object->coords[2] = (fminf(fminf(object->triangle.vert[0][Z], object->triangle.vert[1][Z]), object->triangle.vert[2][Z]) + fmaxf(fmaxf(object->triangle.vert[0][Z], object->triangle.vert[1][Z]), object->triangle.vert[2][Z])) / 2;
	*linep = line;
	return (SUCCESS);
}
