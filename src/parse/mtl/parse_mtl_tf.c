/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_tf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 20:16:37 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/12 20:17:57 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_error	parse_mtl_tf(char *line, t_object *object, t_conf_data *conf)
{
	t_float_rgb	rgb;

	if (object->material.is_enabled.tra_filter)
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KA);
	object->material.is_enabled.tra_filter = true;
	object->material.tra_filter.r = rgb[0] * 255;
	object->material.tra_filter.g = rgb[1] * 255;
	object->material.tra_filter.b = rgb[2] * 255;
	object->material.tra_filter.a = 0xFF;
	return (SUCCESS);
}
