/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:32:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/27 15:30:21 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <libft.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

uint32_t	get_hit_colour(t_scene *scene, t_object *object, t_hit *hit);

bool	shade(t_scene *scene, t_dynarr *hits, uint32_t *pixels)
{
	size_t	i;
	size_t	pixel_index;
	t_hit	*hit;

	(void) scene;
	hit = hits->arr;
	i = hits->length;
	while (i--)
	{
		pixel_index = hit[i].screen_x + hit[i].screen_y * WIDTH;
		pixels[pixel_index] = get_hit_colour(scene, hit[i].object, &hit[i]);
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
	if (times[i][rounds[i]][1] == -1)
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

bool	render(t_mlx_data *mlx, t_scene *scene, size_t width, size_t height)
{
	uint32_t	*pixels;
	t_dynarr	hits;

	stopwatch(1, START, NULL);
	if (!dynarr_create(&hits, width * height / 2, sizeof(t_hit)))
		return (false);
	if (!cast_primary_rays(scene, width, height, &hits))
		return (false); // TODO: dynarr_delete(&hits);
	stopwatch(1, ROUND | SUMMARY, "Primary rays");
	pixels = (uint32_t *) mlx->img->pixels;
	if (!pixels)
		return (false);
	if (!shade(scene, &hits, pixels))
		return (false);
	stopwatch(1, ROUND | SUMMARY, "Shade rays");
	//ft_memcpy(, pixels, width * height * sizeof(uint32_t));
	usleep(1000);
	stopwatch(1, STOP | SUMMARY, "Render done");
	dynarr_delete(&hits);
	stopwatch(1, RESET, NULL);
	return (true);
}
