/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:00:33 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 14:41:16 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include <render.h>

t_fvec	get_uv_colour(t_bmp *texture, float u, float v);

t_fvec	get_texture_cyl(t_hit *hit, t_bmp *texture);
t_fvec	get_texture_face(t_hit *hit, t_bmp *texture);
t_fvec	get_texture_plane(t_hit *hit, t_bmp *texture);
t_fvec	get_texture_sphere(t_hit *hit, t_bmp *texture);
t_fvec	get_texture_triangle(t_hit *hit, t_bmp *texture);

#endif
