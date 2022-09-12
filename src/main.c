/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:31:51 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 18:33:20 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <miniRT.h>
#include <stdlib.h>
#include <parse.h>

int	main(int argc, char *argv[])
{
	t_mlx_data	mlx_data;
	t_scene		scene;

	if (parse_config_file(argc, argv, &scene))
		return (EXIT_FAILURE);
	create_mlx(&mlx_data);
	mlx_loop(mlx_data.mlx);
	mlx_terminate(mlx_data.mlx);
	return (EXIT_SUCCESS);
}
