/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:31:51 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/28 21:59:10 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <bvh.h>
#include <mlx.h>
#include <parse.h>
#include <thread.h>
#include <scene.h>

static bool	init_data(t_minirt *data, int argc, char **argv)
{
	*data = (t_minirt){
		.argv = argv,
		.argc = argc,
		.width = WIDTH,
		.height = HEIGHT
	};
	if (argc == 3)
		return (parse_resolution(data, argv[2]));
	return (true);
}

bool	init_render_data(t_minirt *data)
{
	t_scene	*scene;

	if (!parse_config_file(data->argc, data->argv, &data->scene))
		return (false);
	scene = data->scene;
	calc_ray_info(&scene->camera.camera, data->width, data->height);
	if (!new_bvh(scene->objects, scene->objects_len, &scene->bvh))
		return (false);
	get_scene_scale(scene);
	return (true);
}

static int	cleanup(t_minirt *data, int status)
{
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->scene)
		destroy_scene(data->scene);
	return (status);
}

int	main(int argc, char *argv[])
{
	t_minirt	data;

	if (!init_data(&data, argc, argv) || \
		!init_render_data(&data))
		return (cleanup(&data, EXIT_FAILURE));
	if (HEADLESS)
		return (cleanup(&data, headless(&data)));
	if (!create_mlx(&data) || \
		!init_work_threads(&data))
		return (cleanup(&data, EXIT_FAILURE));
	mlx_loop(data.mlx);
	join_threads(&data);
	return (cleanup(&data, EXIT_SUCCESS));
}
