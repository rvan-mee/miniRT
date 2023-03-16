/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_tr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 18:59:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 16:47:59 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_mtl_tr(char *line, t_object *object)
{
	float	transparency;
	char	*end;
	bool	d;

	d = is_flag(&object->material, DISSOLVED);
	if (is_flag(&object->material, TRANSPARENT))
		return (DUPLICATE);
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (TR);
	transparency = ft_strtof(line, &end);
	if (line == end || !ft_isdigit(end[-1]))
		return (TR);
	line = end;
	skip_spaces(&line);
	if (*line || transparency < 0 || transparency > 1 || \
	(d && object->material.transp_d + transparency != 1))
		return (TR);
	object->material.transp_tr = transparency;
	set_flag(&object->material, TRANSPARENT);
	return (CONTINUE);
}
