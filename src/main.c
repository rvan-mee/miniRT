/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:31:51 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/13 14:53:51 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <miniRT.h>
#include <stdlib.h>
#include <parse.h>


#include <stdio.h>
int	main(int argc, char *argv[])
{
	t_mlx_data	mlx_data;
	t_scene		scene;

	(void)argc;
	(void)argv;
	// if (parse_config_file(argc, argv, &scene))
	// 	return (EXIT_FAILURE);
	create_mlx(&mlx_data);
	if (!parse_rgb("        ,,\n", &scene.ambient.ambient.colour))
		printf("error!\n");
	else
	{
		printf("colour r: %d\n", scene.ambient.ambient.colour.r);
		printf("colour g: %d\n", scene.ambient.ambient.colour.g);
		printf("colour b: %d\n", scene.ambient.ambient.colour.b);
	}
	mlx_loop(mlx_data.mlx);
	mlx_terminate(mlx_data.mlx);
	return (EXIT_SUCCESS);
}
