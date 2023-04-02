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

static bool	is_invalid_value(t_mtl *mtl, float tr)
{
	const bool	d = is_flag(mtl, TRANSPARENT);

	return (tr < 0 || tr > 1 || (d && mtl->transp_d + tr != 1.0f));
}

t_parse_err	parse_mtl_tr(char *line, t_mtl *mtl)
{
	float	transparency;
	char	*end;

	if (is_flag(mtl, TRANSPARENT))
		return (DUPLICATE);
	if (!ft_isdigit(*line))
		return (TR);
	transparency = ft_strtof(line, &end);
	if (line == end || is_invalid_value(mtl, transparency))
		return (TR);
	line = end;
	skip_spaces(&line);
	if (*line)
		return (TR);
	mtl->transp_tr = transparency;
	set_flag(mtl, TRANSPARENT);
	return (CONTINUE);
}
