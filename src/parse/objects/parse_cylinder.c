/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:10:11 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/07 21:20:15 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static void	pre_calc(t_cylinder *cyl)
{
	const float		radius = cyl->diameter / 2;
	const t_fvec	top = cyl->height * cyl->orientation;

	cyl->radius_sq = radius * radius;
	cyl->top = top;
}

t_parse_err	parse_cylinder(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;

	(void) conf;
	line = *linep;
	if (!parse_vector(&line, &object->coords, false) \
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_vector(&line, &object->cylinder.orientation, true) \
		|| !ft_isspace(*line))
		return (VECTOR);
	if (!parse_float(&line, &object->cylinder.diameter, 0, 0)
		|| !ft_isspace(*line))
		return (DIAMETER);
	if (!parse_float(&line, &object->cylinder.height, 0, 0)
		|| !ft_isspace(*line))
		return (OBJ_HEIGHT);
	if (!parse_rgb(&line, &object->colour) || \
		!(ft_isspace(*line) || *line == '\0'))
		return (COLOUR);
	pre_calc(&object->cylinder);
	*linep = line;
	return (SUCCESS);
}
