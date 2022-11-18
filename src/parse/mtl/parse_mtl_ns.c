/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_ns.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 18:03:39 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 16:47:17 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_mtl_ns(char *line, t_object *object)
{
	char	*end;
	float	reflec;

	if (object->material.is_enabled.reflec)
		return (DUPLICATE);
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (ILLUM);
	reflec = ft_strtof(line, &end);
	if (line == end || !ft_isdigit(end[-1]))
		return (ILLUM);
	line = end;
	skip_spaces(&line);
	if (*line)
		return (ILLUM);
	object->material.is_enabled.reflec = true;
	object->material.reflec = reflec;
	return (CONTINUE);
}
