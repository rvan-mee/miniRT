/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:32:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/23 18:13:52 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <thread.h>

uint32_t	get_hit_colour(t_scene *scene, t_object *object, t_hit *hit);

bool	set_color(t_minirt *data, t_dynarr *hits)
{
	size_t		i;
	uint32_t	colour;
	t_hit		*hit;

	hit = hits->arr;
	i = hits->length;
	while (i--)
	{
		colour = get_hit_colour(&data->scene, hit[i].object, &hit[i]);
		mlx_put_pixel(data->img, hit[i].screen_x, hit[i].screen_y, colour);
	}
	return (true);
}

bool	render(t_minirt	*data, t_jobs *job)
{
	const size_t	width = job->end_pixels[X] - job->start_pixels[X];
	const size_t	height = job->end_pixels[Y] - job->start_pixels[Y];
	t_dynarr		hits;
	size_t			screen[2];
	size_t			x;
	size_t			y;

	y = 0;
	if (!dynarr_create(&hits, width, sizeof(t_hit)))
		return (false);
	while (y < height)
	{
		x = 0;
		screen[Y] = job->start_pixels[Y] + y;
		while (x < width)
		{
			screen[X] = job->start_pixels[X] + x;
			if (!trace(&data->scene, &job->rays[y][x], screen, &hits))
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
