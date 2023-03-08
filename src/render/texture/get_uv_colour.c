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

static float	decode_gamma(float component)
{
	if (component < LINEAR_CUTOFF)
		return (component / LINEAR_FACTOR);
	return (powf((GAMMA_B + component) / GAMMA_A, GAMMA));
}

t_fvec	get_uv_colour(t_bmp *texture, float u, float v)
{
	const int32_t	height = texture->height;
	const int32_t	width = texture->width;
	t_rgba			colour;
	uint32_t		offset;

	offset = (((height - (int32_t)(height * v)) * width) + (int32_t)(width * u)) * RGB;
	colour.b = texture->data[offset];
	colour.g = texture->data[offset + 1];
	colour.r = texture->data[offset + 2];
	return ((t_fvec) {
		decode_gamma(colour.r / 255.f),
		decode_gamma(colour.g / 255.f),
		decode_gamma(colour.b / 255.f),
	});
}
