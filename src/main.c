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

void	f(void)
{
	system("leaks -q miniRT");
}

static void	init_data(t_minirt *data, int argc, char **argv)
{
	*data = (t_minirt){
		NULL,
		NULL,
		{},
		argv,
		argc,
		WIDTH,
		HEIGHT,
		{},
		{}
	};
}

static bool	init_render_data(t_minirt *data)
{
	if (!parse_config_file(data->argc, data->argv, &data->scene))
		return (false);
	if (!new_bvh(data->scene.objects, data->scene.objects_len, &data->scene.bvh))
		return (false);
	return (true);
}

#include <unistd.h>
int	main(int argc, char *argv[])
{
	t_minirt	data;

	init_data(&data, argc, argv);
	atexit(f);
	if (!init_render_data(&data))
		return (EXIT_FAILURE);
	create_mlx(&data);
	if (init_work_threads(&data))
	{
		mlx_loop(data.mlx);
		join_threads(&data);
	}
	mlx_terminate(data.mlx);
	exit(EXIT_SUCCESS);
	// free(data.scene.lights);
	// free(data.scene.objects);
	// free(data.texture.bmp->data);
	// free(data.texture.bmp->name);
	return (EXIT_SUCCESS);
}
