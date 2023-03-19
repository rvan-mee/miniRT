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
#include <libft.h>
#include <thread.h>

#define GAMMA_A	1.055f
#define GAMMA_B	0.055f
#define GAMMA	2.4f
#define LINEAR_CUTOFF	0.0031308f
#define LINEAR_FACTOR	12.92f

static uint32_t	encode_gamma(t_fvec rgb)
{
	uint8_t	channel;

	channel = 0;
	while (channel < 3)
	{
		if (rgb[channel] <= LINEAR_CUTOFF)
			rgb[channel] *= LINEAR_FACTOR;
		else
			rgb[channel] = GAMMA_A * powf(rgb[channel], 1.0f / GAMMA) - GAMMA_B;
		++channel;
	}
	return (((uint32_t) fminf(rgb[0] * 0xFF, 255.f)) << 24 | \
			((uint32_t) fminf(rgb[1] * 0xFF, 255.f)) << 16 | \
			((uint32_t) fminf(rgb[2] * 0xFF, 255.f)) << 8 | \
			0xFF);
}

static void	set_color(t_minirt *data, t_dynarr *hits)
{
	size_t		i;
	t_fvec		colour;
	uint32_t	srgb;
	t_hit		*hit;

	hit = hits->arr;
	i = hits->length;
	while (i--)
	{
		colour = shade(data->scene, hit[i].object, &hit[i], 0);
		colour[0] = 1.f - expf(colour[0] * data->scene->camera.camera.exposure);
		colour[1] = 1.f - expf(colour[1] * data->scene->camera.camera.exposure);
		colour[2] = 1.f - expf(colour[2] * data->scene->camera.camera.exposure);
		srgb = encode_gamma(colour);
		mlx_put_pixel(data->img, hit[i].screen_x, hit[i].screen_y, srgb);
	}
}

static bool	trace_row(t_scene *scene, t_render *block, t_dynarr *hits, size_t y)
{
	t_hit	hit;

	hit.screen_y = y;
	hit.screen_x = block->start_pixels[X];
	while (hit.screen_x < block->end_pixels[X])
	{
		hit.ray = get_cam_ray(&scene->camera, hit.screen_x, hit.screen_y);
		if (trace(scene, &hit.ray, &hit) && !dynarr_addone(hits, &hit))
			return (false);
		++hit.screen_x;
	}
	return (true);
}

static bool	render(t_minirt	*data, t_render *block)
{
	const size_t	width = block->end_pixels[X] - block->start_pixels[X];
	t_dynarr		hits;
	bool			status;
	size_t			y;

	y = block->start_pixels[Y];
	if (!dynarr_create(&hits, width, sizeof(t_hit)))
		return (false);
	status = true;
	while (y < block->end_pixels[Y])
	{
		if (!trace_row(data->scene, block, &hits, y))
		{
			status = false;
			break ;
		}
		set_color(data, &hits);
		hits.length = 0;
		y++;
	}
	dynarr_delete(&hits);
	return (status);
}

void	start_render(t_minirt *data, void *func_data)
{
	t_render	*block;

	block = (t_render *)func_data;
	if (!render(data, block))
	{
		quit_working(data->thread);
		clear_job_lst(data->thread);
		mlx_close_window(data->mlx);
	}
	free(block);
}
