/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sphere.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:16:38 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/14 17:28:56 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static void	pre_calc(t_sphere *sphere)
{
	const float	radius = sphere->diameter / 2;

	sphere->radius_sq = radius * radius;
}

t_parse_error	parse_sphere(char **linep, t_object *object)
{
	char	*line;

	line = *linep;
	if (!parse_vector(&line, &object->coords, false)
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_float(&line, &object->sphere.diameter, 0, 0)
		|| !ft_isspace(*line))
		return (DIAMETER);
	if (!parse_rgb(&line, &object->colour))
		return (COLOUR);
	pre_calc(&object->sphere);
	*linep = line;
	return (SUCCESS);
}
