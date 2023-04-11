/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_ns.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 18:03:39 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/04/11 15:48:58 by rvan-mee      ########   odam.nl         */
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
		return (NS);
	reflec = ft_strtof(line, &end);
	if (line == end)
		return (NS);
	line = end;
	skip_spaces(&line);
	if (*line)
		return (NS);
	set_flag(mtl, SPECULAR_EXP);
	mtl->reflec = reflec;
	return (CONTINUE);
}
