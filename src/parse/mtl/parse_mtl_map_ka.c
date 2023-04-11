/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_map_ka.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 17:44:10 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/04/11 17:40:17 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <parse_mtl.h>

t_parse_err	parse_mtl_map_ka(char *line, t_mtl *mtl)
{
	t_parse_err	err;
	t_bmp		tex;

	if (is_flag(mtl, AMBIENT_MAP))
		return (DUP);
	err = parse_mtl_map(line, &tex);
	if (err != SUCCESS)
		return (err);
	set_flag(mtl, AMBIENT_MAP);
	mtl->ambient_tex = tex;
	return (CONTINUE);
}
