/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_kd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:13:45 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/12 17:53:25 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_error	parse_mtl_kd(char *line, t_object *object, t_conf_data *conf)
{
	t_fvec	rgb;

	(void) conf;
	if (object->material.is_enabled.diffuse)
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KD);
	object->material.is_enabled.diffuse = true;
	object->material.diffuse.r = rgb[0] * 255;
	object->material.diffuse.g = rgb[1] * 255;
	object->material.diffuse.b = rgb[2] * 255;
	object->material.diffuse.a = 0xFF;
	return (SUCCESS);
}
