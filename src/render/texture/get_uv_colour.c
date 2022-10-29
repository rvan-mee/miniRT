/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_uv_colour.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 17:00:23 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/29 17:03:11 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <texture.h>

t_rgba	get_uv_colour(t_texture *texture, float u, float v)
{
	const int32_t	height = texture->bmp->height;
	const int32_t	width = texture->bmp->width;
	t_rgba			colour;
	uint32_t		offset;

	offset = (((height - (int32_t)(height * v)) * width) + (int32_t)(width * u)) * RGB;
	colour.b = texture->bmp->data[offset];
	colour.g = texture->bmp->data[offset + 1];
	colour.r = texture->bmp->data[offset + 2];
	colour.a = 0xFF;
	return (colour);
}
