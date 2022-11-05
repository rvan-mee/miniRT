/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:31:51 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/27 15:03:49 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <bvh.h>
#include <mlx.h>
#include <parse.h>

void	f(void)
{
	system("leaks -q miniRT");
}
void	stopwatch(uint8_t i, uint8_t options, const char *arg);

int	main(int argc, char *argv[])
{
	t_minirt	data;

	data.argv = argv;
	data.argc = argc;
	atexit(f);
	if (!parse_config_file(argc, argv, &data.scene) || \
		!new_bvh(data.scene.objects, data.scene.objects_len, &data.scene.bvh))
		return (EXIT_FAILURE);
	create_mlx(&data.mlx_data);
	if (render(&data.mlx_data, &data.scene, WIDTH, HEIGHT))
		mlx_loop(data.mlx_data.mlx);
	mlx_terminate(data.mlx_data.mlx);
	return (EXIT_SUCCESS);
}
