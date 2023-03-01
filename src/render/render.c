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
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <thread.h>

uint32_t	get_hit_colour(t_minirt *data, t_scene *scene, t_object *object, t_hit *hit);

static bool	set_color(t_minirt *data, t_dynarr *hits)
{
	size_t		i;
	uint32_t	colour;
	t_hit		*hit;

	hit = hits->arr;
	i = hits->length;
	while (i--)
	{
		colour = get_hit_colour(data, &data->scene, hit[i].object, &hit[i]);
		mlx_put_pixel(data->img, hit[i].screen_x, hit[i].screen_y, colour);
	}
	return (true);
}

enum sw_opt {
	START = 1 << 0,
	STOP = 1 << 1,
	RESET = 1 << 2,
	ROUND = 1 << 3,
	PRINT = 1 << 4,
	SUMMARY = 1 << 5
};

#define t(x) ((x) / (long double) (CLOCKS_PER_SEC / 1000))
#define o_str(s) s == START ? "Running" : "Stopped"
void	stopwatch(uint8_t i, uint8_t options, const char *arg)
{
	static long double	times[10][16][2];
	static uint8_t		rounds[10];
	static uint8_t		status[10];
	long double			total_t;
//	long double			round_t[16];


	if (options & START)
	{
		status[i] = START;
		times[i][rounds[i]][0] = clock();
		times[i][rounds[i]][1] = -1;
	}
	if (options & STOP)
	{
		status[i] = STOP;
		times[i][rounds[i]][1] = clock();
		++rounds[i];
	}
	if (options & RESET)
	{
		status[i] = STOP;
		rounds[i] = 0;
		times[i][0][0] = -1;
		times[i][0][1] = -1;
	}
	if (options & ROUND)
	{
		times[i][rounds[i]][1] = clock();
		times[i][rounds[i] + 1][0] = times[i][rounds[i]][1];
		times[i][rounds[i] + 1][1] = -1;
		++rounds[i];
	}
	if (!((options & SUMMARY) || (options & PRINT)))
		return;
//	long double cur = clk();
	total_t = 0;
	if (rounds[i] == 0)
		total_t = (clock()) - times[i][rounds[i]][0];
	else
		for (uint8_t j = 0; j < rounds[i]; j++)
			total_t += times[i][j][1] - times[i][j][0];

	if (options & SUMMARY)
	{
		printf("%s%c\t%6.6Lf ms\t%2u rounds (%6.6Lf ms avg)\n",
			   arg, status[i] == START ? '*' : ' ', t(total_t), rounds[i], t(total_t / rounds[i]));
	}
	if (options & PRINT)
	{
		printf("Stopwatch %d: %s\n", i, o_str(status[i]));

	}
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
