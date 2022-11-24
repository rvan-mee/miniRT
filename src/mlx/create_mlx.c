/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_mlx.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:32:16 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/20 18:28:14 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <minirt.h>
#include <stdlib.h>
#include <libft.h>
#include <math.h>
#include "ft_math.h"
#include <render.h>

static t_ray	get_ray(t_minirt *data, size_t x, size_t y)
{
	const float	aspect = (float) data->width / (float) data->height;
	const float width = tanf(data->scene.camera.camera.fov / 2);
	const float height = width / aspect;
	t_ray	ray;
	t_fvec	coords;

	ray.origin = data->scene.camera.coords;
	// use offset from camera direction
	coords[X] = ((float) x + 0.5f) / (float) data->width;
	coords[Y] = ((float) y + 0.5f) / (float) data->height;
	coords[X] = 2 * coords[X] - 1;
	coords[Y] = 1 - 2 * coords[Y];
	coords[X] *= width;
	coords[Y] *= height;
	coords[Z] = 1;
	ray.direction = normalize_vector(coords);
	return (ray);
}


static void	mouse(mouse_key_t type, action_t action, modifier_key_t mod, t_minirt *data)
{
	(void) type, (void) mod;
	if (action != MLX_PRESS)
		return;
	t_hit		hit;
	t_dynarr	hits = {&hit, sizeof(t_hit), 1, 0};
	int32_t		x, y;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	size_t		screen[2] = {x, y};
	t_ray		ray = get_ray(data, screen[X], screen[Y]);
	if (trace(&data->scene, &ray, screen, &hits))
	{
		printf("hit at (%lu,%lu) ==> (%f, %f, %f) == objects[%lu]\n", screen[X], screen[Y],
			hit.hit[X], hit.hit[Y], hit.hit[Z], hit.object - data->scene.objects);
	}
}

void	create_mlx(t_minirt	*data)
{
	data->mlx = mlx_init(data->width, data->height, "miniRT", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	mlx_set_window_pos(data->mlx, 0, 0);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img \
		|| mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_terminate(data->mlx);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(data->mlx, (mlx_keyfunc)keyhook, data);
	mlx_mouse_hook(data->mlx, (mlx_mousefunc)mouse, data);
}
