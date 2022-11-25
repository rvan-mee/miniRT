/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_ke.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:18:06 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 13:06:33 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_error	parse_mtl_ke(char *line, t_object *object)
{
	t_fvec	rgb;

	if (object->material.is_enabled.emmis_col)
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KE);
	object->material.is_enabled.emmis_col = true;
	object->material.emmis_col = rgb;
	return (CONTINUE);
}
