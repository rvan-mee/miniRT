/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_texture_cyl.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 12:30:56 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 14:41:47 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>

t_fvec	get_texture_cyl(t_hit *hit, t_bmp *texture)
{
	(void) hit;
	(void) texture;
	return ((t_fvec){1, 1, 1});
}
