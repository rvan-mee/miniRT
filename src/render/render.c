/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:32:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/07 13:47:12 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <thread.h>
#include <inttypes.h>
#include <string.h>
#include <ft_math.h>

#define GAMMA_A	1.055f
#define GAMMA_B	0.055f
#define GAMMA	2.4f
#define LINEAR_CUTOFF	0.0031308f
#define LINEAR_FACTOR	12.92f

#ifndef MAX_SAMPLES
# define MAX_SAMPLES	16
#endif
#ifndef SMART_AA
# define SMART_AA		1
#endif

static uint32_t	encode_gamma(t_fvec rgb)
{
	uint8_t		channel;
	uint32_t	colour;

	channel = 0;
	while (channel < 3)
	{
		if (rgb[channel] <= LINEAR_CUTOFF)
			rgb[channel] *= LINEAR_FACTOR;
		else
			rgb[channel] = GAMMA_A * powf(rgb[channel], 1.0f / GAMMA) - GAMMA_B;
		++channel;
	}
	rgb[3] = 1.0f;
	rgb = min_vec(rgb * 0xFF, (t_fvec){255.f, 255.f, 255.f, 255.f});
	// This produces a little endian uint on linux -- mlx_put_pixel does not
	// seem to like that very much, but we can assign it to the pixels (if they
	// are cast to a uint32_t *) directly!
	colour = (uint32_t) __builtin_convertvector(rgb, t_bvec);
	return (colour);
}

static void	put_pixel(mlx_image_t *img, uint32_t col, int32_t x, int32_t y)
{
//	mlx_put_pixel(img, x, y, col);
	const int32_t	offs = (y * (int32_t) img->width + x);
	uint32_t		*px;

	px = (uint32_t *) img->pixels;
	px[offs] = col;
}

/*
 * 0: Just the center pixel
 * 1-2: 2x super sampling
 * 1-4: 4x
 * 1-8: 8x
 * 1-16: 16x
 */
static const t_fvec2	g_aa_offs[] = {
	{0.50f, 0.50f},
	{0.35f, 0.05f}, {0.65f, 0.95f},
	{0.05f, 0.65f}, {0.95f, 0.35f},
	{0.45f, 0.35f}, {0.55f, 0.65f}, {0.35f, 0.55f}, {0.65f, 0.45f},
	{0.55f, 0.15f}, {0.45f, 0.85f}, {0.15f, 0.45f}, {0.85f, 0.55f},
	{0.75f, 0.25f}, {0.25f, 0.75f}, {0.25f, 0.25f}, {0.75f, 0.75f},
};

bool	enough_hits(t_hit hits[], size_t samp, size_t hit_i)
{
	uint32_t	counted;
	uint8_t		hit_c[MAX_SAMPLES + 1];
	size_t		i;
	size_t		j;

	if (hit_i == 0)
		return (true);
	bzero(hit_c, sizeof(hit_c));
	i = hit_i;
	counted = 0;
	while (i--)
	{
		if (counted & (1 << i))
			continue ;
		hit_c[i]++;
		counted |= (1 << i);
		j = i;
		while (j--)
		{
			if ((counted & (1 << j)) || \
				hits[i].object != hits[j].object)
				continue ;
			hit_c[i]++;
			counted |= (1 << j);
		}
	}
	if (hit_c[hit_i - 1] == samp + 1)
		return (true);
	// Previous if will return if all values are the same
	if (samp == 2)
		return (false);
	counted = 0;
	j = 0;
	i = 0;
	while (i < hit_i)
		counted += hit_c[i++], j++;
	if (samp == 4) // At most 2 diff objs
		return (j + (counted != samp + 1) <= 2);
//	if (sample == 8) // At most 3 diff objs
	return (j + (counted != samp + 1) <= 4);
}

/*
 * Uses slightly modified rotated grid anti aliasing.
 *
 * More importantly, checks if there's been more than one object we collided
 * with (or it's reflective/refractive) so we don't need to supersample every
 * pixel.
 */
static void	render_pixel(t_minirt *data, int32_t x, int32_t y)
{
	t_hit	hits[MAX_SAMPLES + 1];
	size_t	hit_i;
	size_t	samp;
	t_fvec2	pos;

	hit_i = 0;
	samp = 0;
	while (samp <= MAX_SAMPLES)
	{
		pos = (t_fvec2){(float)x, (float)y} + g_aa_offs[samp];
		hits[hit_i].ray = get_cam_ray(&data->scene->camera, pos[X], pos[Y]);
		hits[hit_i].inside_ri = 1.0f;
		if (trace(data->scene, &hits[hit_i].ray, hits + hit_i))
			hit_i++;
		if (SMART_AA && (samp == 2 || samp == 4 || samp == 8) && \
			enough_hits(hits, samp, hit_i))
			break ;
		++samp;
	}
	t_fvec col = {};
	while (hit_i--)
		col += shade(data->scene, hits + hit_i, 1.0f);
	if (samp <= MAX_SAMPLES)
		samp++;
	col /= (float) samp;
	col = 1.0f - exp_fvec(col * data->scene->camera.camera.exposure);
	put_pixel(data->img, encode_gamma(col), x, y);
}

static void	render(t_minirt	*data, t_render *block)
{
	const t_ivec	end = block->start + block->size;
	int32_t			x;
	int32_t			y;

	y = block->start[Y];
	while (y < end[Y])
	{
		x = block->start[X];
		while (x < end[X])
		{
			render_pixel(data, x, y);
			++x;
		}
		y++;
	}
}

void	start_render(t_minirt *data, void *func_data)
{
	t_render	*block;

	block = (t_render *)func_data;
	render(data, block);
}
