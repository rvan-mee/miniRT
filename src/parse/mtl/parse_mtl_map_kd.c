/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_map_kd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 12:03:28 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/25 20:54:08 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <parse_mtl.h>

t_parse_error	parse_mtl_map_kd(char *line, t_object *object)
{
	t_parse_error	err;
	t_bmp			tex;

	err = parse_mtl_map(line, &tex);
	if (err != SUCCESS)
		return (err);
	set_flag(&object->material, DIFFUSE_MAP);
	object->material.map_Kd = tex;
	return (CONTINUE);
}
