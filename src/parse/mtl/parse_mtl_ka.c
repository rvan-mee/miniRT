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

t_parse_error	parse_mtl_ka(char *line, t_object *object)
{
	t_fvec	rgb;

	if (object->material.is_enabled.ambient)
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KA);
	object->material.is_enabled.ambient = true;
	object->material.ambient = rgb;
	return (CONTINUE);
}
