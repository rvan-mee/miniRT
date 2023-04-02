/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_tf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 20:16:37 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 16:47:57 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_parse_err	parse_mtl_tf(char *line, t_mtl *mtl)
{
	if (is_flag(mtl, TRANSMISSION_FILTER))
		return (DUPLICATE);
	if (!parse_float_rgb(&line, &mtl->tra_filter))
		return (KA);
	set_flag(mtl, TRANSMISSION_FILTER);
	return (CONTINUE);
}
