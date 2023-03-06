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

static bool	set_color(t_minirt *data, t_dynarr *hits)
{
	size_t	i;
	t_fvec	colour;
	t_rgba	rgba;
	t_hit	*hit;

	hit = hits->arr;
	i = hits->length;
	while (i--)
	{
		colour = get_hit_colour(&data->scene, hit[i].object, &hit[i], 0);
		rgba = (t_rgba){
			.r = (uint8_t) fminf(colour[0] * 255, 255.f),
			.g = (uint8_t) fminf(colour[1] * 255, 255.f),
			.b = (uint8_t) fminf(colour[2] * 255, 255.f),
			.a = 0xFF
		};
		mlx_put_pixel(data->img, hit[i].screen_x, hit[i].screen_y, rgba.rgba);
	}
	return (true);
}

static bool	render(t_minirt	*data, t_render *block, \
					size_t width, size_t height)
{
	t_dynarr		hits;
	size_t			screen[2];
	size_t			x;
	size_t			y;
	t_ray			ray;

	y = 0;
	if (!dynarr_create(&hits, width, sizeof(t_hit)))
		return (false);
	while (y < height)
	{
		x = 0;
		screen[Y] = block->start_pixels[Y] + y;
		while (x < width)
		{
			screen[X] = block->start_pixels[X] + x;
			ray = get_cam_ray(&data->scene.camera, screen[X], screen[Y]);
			if (!trace(&data->scene, &ray, screen, &hits))
				return (false); // TODO: dynarr_delete(&hits);
			x++;
		}
		if (!set_color(data, &hits))
			return (false); // TODO: dynarr_delete(&hits);
		hits.length = 0;
		y++;
	}
	dynarr_delete(&hits);
	return (true);
}

static void	free_data(t_minirt *data, t_render *block)
{
	quit_working(data);
	free(block);
	pthread_mutex_lock(&data->thread.job_lock);
	clear_job_lst(data);
	mlx_close_window(data->mlx);
	pthread_mutex_unlock(&data->thread.job_lock);
}

void	start_render(t_minirt *data, void *func_data)
{
	size_t		width;
	size_t		height;
	t_render	*block;

	block = (t_render *)func_data;
	width = block->end_pixels[X] - block->start_pixels[X];
	height = block->end_pixels[Y] - block->start_pixels[Y];
	if (!render(data, block, width, height))
		free_data(data, block);
	else
		free(block);
}
