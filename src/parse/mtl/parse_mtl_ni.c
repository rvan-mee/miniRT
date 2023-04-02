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

t_parse_err	parse_mtl_ni(char *line, t_mtl *mtl)
{
	float	density;
	char	*end;

	if (is_flag(mtl, REFRACT_IDX))
		return (DUPLICATE);
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (NI);
	density = ft_strtof(line, &end);
	if (line == end)
		return (NI);
	line = end;
	skip_spaces(&line);
	if (*line)
		return (NI);
	mtl->opt_dens = density;
	set_flag(mtl, REFRACT_IDX);
	return (CONTINUE);
}
