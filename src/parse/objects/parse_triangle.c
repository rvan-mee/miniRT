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

static void	pre_calc(t_object *obj)
{
	const t_aabb	bounds = calc_bounds(obj);
	t_triangle		*tr;

	obj->coords = (bounds.min + bounds.max) / 2.f;
	tr = &obj->triangle;
	tr->v0v1 = tr->vert[1] - tr->vert[0];
	tr->v0v2 = tr->vert[2] - tr->vert[0];
}

t_parse_err	parse_triangle(char **linep, t_object *object, t_conf_data *conf)
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
	pre_calc(object);
	*linep = line;
	return (SUCCESS);
}
