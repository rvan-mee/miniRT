/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reload_scene.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 10:20:51 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/09 10:20:51 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <scene.h>
#include <mlx.h>
#include <thread.h>

static void	panic_time(t_minirt *data)
{
	perror("Unrecoverable error while reloading scene");
	quit_working(data->thread);
	mlx_close_window(data->mlx);
}

void	reload_scene(t_minirt *data, enum keys key)
{
	t_object	old_cam;

	(void) key;
	old_cam = data->scene->camera;
	destroy_scene(data->scene);
	if (!init_render_data(data))
		return (panic_time(data));
	data->scene->camera = old_cam;
	mlx_resize_image(data->img, data->width, data->height);
	mlx_set_window_size(data->mlx, data->width, data->height);
	reset_work(data);
}
