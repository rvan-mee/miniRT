/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_ke.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:18:06 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/12 17:53:38 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_error	parse_mtl_ke(char *line, t_object *object, t_conf_data *conf)
{
	t_fvec	rgb;

	(void) conf;
	if (object->material.is_enabled.emmis_col)
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KE);
	object->material.is_enabled.emmis_col = true;
	object->material.emmis_col.r = rgb[0] * 255;
	object->material.emmis_col.g = rgb[1] * 255;
	object->material.emmis_col.b = rgb[2] * 255;
	object->material.emmis_col.a = 0xFF;
	return (SUCCESS);
}