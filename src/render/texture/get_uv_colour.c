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
#include <math.h>

#define GAMMA_A	1.055f
#define GAMMA_B	0.055f
#define GAMMA	2.4f
#define LINEAR_CUTOFF	0.04045f
#define LINEAR_FACTOR	12.92f

static t_fvec	decode_gamma(t_fvec col)
{
	uint8_t	idx;

	idx = 0;
	while (idx < 3)
	{
		if (col[idx] < LINEAR_CUTOFF)
			col[idx] /= LINEAR_FACTOR;
		else
			col[idx] = powf((GAMMA_B + col[idx]) / GAMMA_A, GAMMA);
		++idx;
	}
	return (col);
}

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
