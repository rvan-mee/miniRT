/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:00:33 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/16 17:13:19 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

#include <minirt.h>
#include <bmp.h>

t_rgba	get_uv_colour(t_bmp *texture, float u, float v);
t_rgba	get_texture_colour_sphere(t_hit *hit, t_bmp *texture);

#endif	// texture.h
