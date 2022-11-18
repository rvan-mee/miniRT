/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_uv_colour.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 17:00:23 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/16 17:13:52 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <texture.h>

t_rgba	get_uv_colour(t_bmp *texture, float u, float v)
{
	const int32_t	height = texture->height;
	const int32_t	width = texture->width;
	t_rgba			colour;
	uint32_t		offset;

	offset = (((height - (int32_t)(height * v)) * width) + (int32_t)(width * u)) * RGB;
	colour.b = texture->data[offset];
	colour.g = texture->data[offset + 1];
	colour.r = texture->data[offset + 2];
	colour.a = 0xFF;
	return (colour);
}
