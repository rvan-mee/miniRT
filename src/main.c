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

void	f(void)
{
	system("leaks -q miniRT");
}

static void	init_data(t_minirt *data, int argc, char **argv)
{
	*data = (t_minirt){
		.argv = argv,
		.argc = argc,
		.width = WIDTH,
		.height = HEIGHT
	};
}

bool	init_render_data(t_minirt *data)
{
	t_scene	**scenep;
	t_scene	*scene;

	scenep = &data->scene;
	if (!parse_config_file(data->argc, data->argv, scenep))
		return (false);
	scene = *scenep;
	if (!new_bvh(scene->objects, scene->objects_len, &scene->bvh))
		return (false);
	get_scene_scale(scene);
	return (true);
}

static int	cleanup(t_minirt *data, int status)
{
	size_t	i;

	if (data->mlx)
		mlx_terminate(data->mlx);
	i = 0;
	while (i < data->scene->materials_len)
	{
		free(data->scene->materials[i].map_Ka.data);
		free(data->scene->materials[i].map_Kd.data);
		free(data->scene->materials[i].map_Ks.data);
		free(data->scene->materials[i].name);
		i++;
	}
	free(data->scene->materials);
	free(data->scene->lights);
	free(data->scene->objects);
	free(data->scene->bvh.clusters);
	free(data->scene);
	return (status);
}

int	main(int argc, char *argv[])
{
	t_minirt	data;

	init_data(&data, argc, argv);
	atexit(f);
	if (!init_render_data(&data) || \
		!create_mlx(&data) || \
		!init_work_threads(&data))
		return (cleanup(&data, EXIT_FAILURE));
	mlx_loop(data.mlx);
	join_threads(&data);
	return (cleanup(&data, EXIT_SUCCESS));
}
