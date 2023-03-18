/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_d.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 18:59:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 16:47:30 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_err	parse_mtl_d(char *line, t_object *object)
{
	float	transparency;
	char	*end;
	bool	tr;

	tr = is_flag(&object->material, TRANSPARENT);
	if (is_flag(&object->material, DISSOLVED))
		return (DUPLICATE);
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (D);
	transparency = ft_strtof(line, &end);
	if (line == end || !ft_isdigit(end[-1]))
		return (D);
	line = end;
	skip_spaces(&line);
	if (*line || transparency < 0 || transparency > 1 || \
	(tr && object->material.transp_tr + transparency != 1))
		return (D);
	object->material.transp_d = transparency;
	set_flag(&object->material, DISSOLVED);
	return (CONTINUE);
}
