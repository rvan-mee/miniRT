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

t_parse_err	parse_mtl_ns(char *line, t_mtl *mtl)
{
	char	*end;
	float	reflec;

	if (is_flag(mtl, SPECULAR_EXP))
		return (DUPLICATE);
	if (!ft_isdigit(*line))
		return (ILLUM);
	reflec = ft_strtof(line, &end);
	if (line == end)
		return (ILLUM);
	line = end;
	skip_spaces(&line);
	if (*line)
		return (ILLUM);
	set_flag(mtl, SPECULAR_EXP);
	mtl->reflec = reflec;
	return (CONTINUE);
}
