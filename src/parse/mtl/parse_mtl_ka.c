/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_ka.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:06:36 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 13:06:08 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_err	parse_mtl_ka(char *line, t_mtl *mtl)
{
	t_fvec	rgb;

	if (is_flag(mtl, AMBIENT_C))
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KA);
	set_flag(mtl, AMBIENT_C);
	mtl->ambient = rgb;
	return (CONTINUE);
}
