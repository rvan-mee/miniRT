/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_triangle_hit_colour.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 18:36:03 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 14:41:41 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <texture.h>

t_fvec	get_texture_triangle(t_hit *hit, t_bmp *texture)
{
	(void) hit;
	(void) texture;
	return ((t_fvec){1, 1, 1});
}
