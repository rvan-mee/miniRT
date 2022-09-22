/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:31:51 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/22 19:10:31 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <parse.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_mlx_data	mlx_data;
	t_scene		scene;

	if (!parse_config_file(argc, argv, &scene))
		return (EXIT_FAILURE);
	else
		printf("parsing successful\n");
	create_mlx(&mlx_data);
	if (render(&mlx_data, &scene, WIDTH, HEIGHT))
		mlx_loop(mlx_data.mlx);
	mlx_terminate(mlx_data.mlx);
	return (EXIT_SUCCESS);
}
