/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gamma.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 16:02:03 by lsinke        #+#    #+#                 */
/*   Updated: 2023/04/10 16:02:03 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>

#define GAMMA_A			1.055f
#define GAMMA_B			0.055f
#define GAMMA			2.4f
#define LINEAR_CUTOFF	0.04045f
#define LINEAR_FACTOR	12.92f

// Dat zeg ik..

t_fvec	decode_gamma(t_fvec srgb)
{
	uint8_t	channel;

	channel = 0;
	while (channel < 3)
	{
		if (srgb[channel] < LINEAR_CUTOFF)
			srgb[channel] /= LINEAR_FACTOR;
		else
			srgb[channel] = powf((GAMMA_B + srgb[channel]) / GAMMA_A, GAMMA);
		++channel;
	}
	return (srgb);
}

t_fvec	encode_gamma(t_fvec rgb)
{
	uint8_t		channel;

	channel = 0;
	while (channel < 3)
	{
		if (rgb[channel] < LINEAR_CUTOFF / LINEAR_FACTOR)
			rgb[channel] *= LINEAR_FACTOR;
		else
			rgb[channel] = GAMMA_A * powf(rgb[channel], 1.0f / GAMMA) - GAMMA_B;
		++channel;
	}
	return (rgb);
}
