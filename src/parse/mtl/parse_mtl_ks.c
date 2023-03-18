/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_ks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:15:13 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 13:06:44 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_err	parse_mtl_ks(char *line, t_object *object)
{
	t_fvec	rgb;

	if (is_flag(&object->material, SPECULAR_C))
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &rgb))
		return (KS);
	set_flag(&object->material, SPECULAR_C);
	object->material.specular = rgb;
	return (CONTINUE);
}
