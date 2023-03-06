/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_texture_plane.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 12:30:18 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 14:41:30 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_fvec	get_texture_plane(t_hit *hit, t_bmp *texture)
{
	(void) hit;
	(void) texture;
	return ((t_fvec) {1, 1, 1});
}
