/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_map_kd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 12:03:28 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/04/11 17:39:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <parse_mtl.h>

t_parse_err	parse_mtl_map_kd(char *line, t_mtl *mtl)
{
	t_parse_err	err;
	t_bmp		tex;

	if (is_flag(mtl, DIFFUSE_MAP))
		return (DUP);
	err = parse_mtl_map(line, &tex);
	if (err != SUCCESS)
		return (err);
	set_flag(mtl, DIFFUSE_MAP);
	mtl->diffuse_tex = tex;
	return (CONTINUE);
}
