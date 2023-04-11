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
#include <ft_math.h>

static void	put_pixel(mlx_image_t *img, uint32_t col, int32_t x, int32_t y)
{
	const int32_t	offs = (y * (int32_t) img->width + x);
	uint32_t		*px;

	px = (uint32_t *) img->pixels;
	px[offs] = col;
}

static void	no_supersampling(t_minirt *data, int32_t x, int32_t y)
{
	t_hit		hit;
	t_fvec2		pos;
	t_fvec		colour;
	uint32_t	pix_col;

	pos = (t_fvec2){(float) x, (float) y} + 0.5f;
	hit.ray = get_cam_ray(&data->scene->camera, pos[X], pos[Y]);
	hit.inside_ri = 1.0f;
	if (!trace(data->scene, &hit.ray, &hit))
		return (put_pixel(data->img, 0xFF000000, x, y));
	colour = shade(data->scene, &hit, 1.0f);
	colour = 1.0f - exp_fvec(colour * data->scene->camera.camera.exposure);
	colour = encode_gamma(colour);
	colour[3] = 1.0f;
	colour = min_vec(colour * 0xFF, (t_fvec){255.f, 255.f, 255.f, 255.f});
	pix_col = (uint32_t) __builtin_convertvector(colour, t_bvec);
	put_pixel(data->img, pix_col, x, y);
}

/*
 * Uses slightly modified rotated grid antialiasing.
 *
 * More importantly, checks if there's been more than one object we collided
 * with (or it's reflective/refractive) so we don't need to supersample every
 * pixel.
 */
static void	render_pixel(t_minirt *data, int32_t x, int32_t y)
{
	t_sinfo	info;
	t_fvec	col;

	if (MAX_SAMPLES == 0)
		return (no_supersampling(data, x, y));
	info = (t_sinfo){};
	cast_cam_rays(data->scene, &info, x, y);
	if (info.hit_count == 0)
		return (put_pixel(data->img, 0xFF000000, x, y));
	col = shade_samples(data->scene, &info);
	col = 1.0f - exp_fvec(col * data->scene->camera.camera.exposure);
	col = encode_gamma(col);
	col[3] = 1.0f;
	col = min_vec(col * 0xFF, (t_fvec){255.f, 255.f, 255.f, 255.f});
	put_pixel(data->img, (uint32_t) __builtin_convertvector(col, t_bvec), x, y);
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
