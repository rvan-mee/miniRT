/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_map_ks.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 17:45:04 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/04/11 17:40:25 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <parse_mtl.h>

t_parse_err	parse_mtl_map_ks(char *line, t_mtl *mtl)
{
	t_parse_err	err;
	t_bmp		tex;

	if (is_flag(mtl, SPECULAR_MAP))
		return (DUP);
	err = parse_mtl_map(line, &tex);
	if (err != SUCCESS)
		return (err);
	set_flag(mtl, SPECULAR_MAP);
	mtl->specular_tex = tex;
	return (CONTINUE);
}
