/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:10:11 by rvan-mee      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/11/07 21:01:56 by rvan-mee      ########   odam.nl         */
=======
/*   Updated: 2022/11/06 15:34:13 by rvan-mee      ########   odam.nl         */
>>>>>>> v, vt and vn parsing done, face rendering too. check for norm and if everything works properly next up.
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

t_parse_error	parse_cylinder(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;

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
