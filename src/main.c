/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:31:51 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/24 20:21:18 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <parse.h>
#include <stdio.h>
#include <thread.h>

// void	f(void)
// {
// 	system("leaks -q miniRT");
// }

int	main(int argc, char *argv[])
{
	t_minirt	data;

	data.argv = argv;
	data.argc = argc;
	data.width = WIDTH;
	data.height = HEIGHT;
	data.thread.job_lst = NULL;
	// atexit(f);
	if (!parse_config_file(argc, argv, &data.scene))
		return (EXIT_FAILURE);
	create_mlx(&data);
	if (init_work_threads(&data))
	{
		mlx_loop(data.mlx);
		join_threads(&data);
	}
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
