/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_kd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:13:45 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 13:06:23 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_err	parse_mtl_kd(char *line, t_mtl *mtl)
{
	t_fvec	rgb;

	if (is_flag(mtl, DIFFUSE_C))
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KD);
	set_flag(mtl, DIFFUSE_C);
	mtl->diffuse = rgb;
	return (CONTINUE);
}
