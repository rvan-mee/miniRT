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

#include <mlx.h>
#include <thread.h>
#include <stdlib.h>

static void	destroy_scene(t_scene *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->materials_len)
	{
		free(scene->materials[i].map_Ka.data);
		free(scene->materials[i].map_Kd.data);
		free(scene->materials[i].map_Ks.data);
		free(scene->materials[i].name);
		i++;
	}
	free(scene->materials);
	free(scene->lights);
	free(scene->objects);
	free(scene->bvh.clusters);
}

static void	panic_time(t_minirt *data)
{
	perror("Unrecoverable error while reloading scene");
	quit_working(data);
	mlx_close_window(data->mlx);
}

void	reload_scene(t_minirt *data, enum keys key)
{
	t_object	old_cam;

	(void) key;
	old_cam = data->scene.camera;
	destroy_scene(&data->scene);
	data->scene = (t_scene){};
	if (!init_render_data(data))
		return (panic_time(data));
	data->scene.camera = old_cam;
	mlx_resize_image(data->img, data->width, data->height);
	mlx_set_window_size(data->mlx, data->width, data->height);
	reset_work(data);
}
