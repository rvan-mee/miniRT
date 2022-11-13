/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_ks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:15:13 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/12 17:53:48 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_error	parse_mtl_ks(char *line, t_object *object, t_conf_data *conf)
{
	t_fvec	rgb;

	(void) conf;
	if (object->material.is_enabled.specular)
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KS);
	object->material.is_enabled.specular = true;
	object->material.specular.r = rgb[0] * 255;
	object->material.specular.g = rgb[1] * 255;
	object->material.specular.b = rgb[2] * 255;
	object->material.specular.a = 0xFF;
	return (SUCCESS);
}