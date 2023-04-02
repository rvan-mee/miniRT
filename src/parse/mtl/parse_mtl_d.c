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

static bool	is_invalid_value(t_mtl *mtl, float d)
{
	const bool	tr = is_flag(mtl, TRANSPARENT);

	return (d < 0 || d > 1 || (tr && mtl->transp_tr + d != 1.0f));
}

t_parse_err	parse_mtl_d(char *line, t_mtl *mtl)
{
	float	transparency;
	char	*end;

	if (is_flag(mtl, DISSOLVED))
		return (DUPLICATE);
	if (!ft_isdigit(*line))
		return (D);
	transparency = ft_strtof(line, &end);
	if (line == end || is_invalid_value(mtl, transparency))
		return (D);
	line = end;
	skip_spaces(&line);
	if (*line)
		return (D);
	mtl->transp_d = transparency;
	set_flag(mtl, DISSOLVED);
	return (CONTINUE);
}
