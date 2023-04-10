/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_uv_colour.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 17:00:23 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/03/08 18:06:02 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <texture.h>

t_fvec	get_uv_colour(t_bmp *texture, float u, float v)
{
	const uint32_t	x = (uint32_t)((float) texture->width * u);
	const uint32_t	y = (uint32_t)((float) texture->height * (1.f - v));
	t_fvec			colour;
	uint32_t		offset;

	offset = x * texture->pixel_size + y * texture->line_size;
	colour[2] = texture->data[offset];
	colour[1] = texture->data[offset + 1];
	colour[0] = texture->data[offset + 2];
	colour /= 255.f;
	return (decode_gamma(colour));
}
