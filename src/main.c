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
#include <stdio.h>
#include <thread.h>
#include <texture.h>

void	f(void)
{
	system("leaks -q miniRT");
}
void	stopwatch(uint8_t i, uint8_t options, const char *arg);

#include <unistd.h>
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
		exit(EXIT_SUCCESS);
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
