/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_ke.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:18:06 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 13:06:33 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_err	parse_mtl_ke(char *line, t_mtl *mtl)
{
	t_fvec	rgb;

	if (is_flag(mtl, EMMISIVE_C))
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KE);
	set_flag(mtl, EMMISIVE_C);
	mtl->emmis_col = rgb;
	return (CONTINUE);
}
