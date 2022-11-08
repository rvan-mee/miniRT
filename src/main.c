/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:31:51 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/25 14:24:08 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <bvh.h>
#include <mlx.h>
#include <parse.h>
#include <stdio.h>
#include <thread.h>

#define NO_THREADS	0

void	f(void)
{
	system("leaks -q miniRT");
}
void	stopwatch(uint8_t i, uint8_t options, const char *arg);

static bool	render_single(t_minirt *data)
{
	t_render	*b = malloc(sizeof(t_render));
	*b = (t_render){
			{0, 0},
			{1920, 1080},
			{1920, 1080},
			data->scene.camera,
			NULL
	};
	start_render(data, b);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_minirt	data;

	data.argv = argv;
	data.argc = argc;
	data.width = WIDTH;
	data.height = HEIGHT;
	data.thread.job_lst = NULL;
	atexit(f);
	if (!parse_config_file(argc, argv, &data.scene) || \
		!new_bvh(data.scene.objects, data.scene.objects_len, &data.scene.bvh))
		return (EXIT_FAILURE);
	create_mlx(&data);
	if ((NO_THREADS && render_single(&data)) || init_work_threads(&data))
		mlx_loop(data.mlx);
	if (!NO_THREADS)
		join_threads(&data);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
