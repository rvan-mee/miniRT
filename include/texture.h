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

# include <minirt.h>
# include <bmp.h>

t_rgba	get_uv_colour(t_bmp *texture, float u, float v);

t_rgba	get_cyl_hit_colour(t_object *object, t_hit *hit);
t_rgba	get_face_hit_colour(t_object *object, t_hit *hit);
t_rgba	get_plane_hit_colour(t_object *object, t_hit *hit);
t_rgba	get_sphere_hit_colour(t_object *object, t_hit *hit);
t_rgba	get_tri_hit_colour(t_object *object, t_hit *hit);

#endif	// texture.h
