/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_ni.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 20:12:30 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 16:47:54 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_mtl_ni(char *line, t_object *object)
{
	float	density;
	char	*end;

	if (is_flag(&object->material, REFRACT_IDX))
		return (DUPLICATE);
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (D);
	density = ft_strtof(line, &end);
	if (line == end || !ft_isdigit(end[-1]))
		return (D);
	line = end;
	skip_spaces(&line);
	if (*line)
		return (D);
	object->material.opt_dens = density;
	set_flag(&object->material, REFRACT_IDX);
	return (CONTINUE);
}
