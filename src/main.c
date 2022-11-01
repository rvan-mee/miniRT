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

#include <mlx.h>
#include <stdlib.h>
#include <parse.h>
#include <stdio.h>
#include <x86intrin.h>
#include <time.h>
#include <bvh.h>

void	f(void)
{
	system("leaks -q miniRT");
}
void	stopwatch(uint8_t i, uint8_t options, const char *arg);

#define TEST_SIZE 7000000
int	main(int argc, char *argv[])
{
	t_minirt	data;
	t_bvh		bvh;

	t_object	*objs = malloc(TEST_SIZE * sizeof(t_object));
	srand(clock());
	for (int i = 0; i < TEST_SIZE; i++)
	{
		objs[i].type = SPHERE;
		objs[i].sphere.diameter = (5 * (rand() / (float) RAND_MAX));
		objs[i].coords = (t_fvec){(double) rand() / (float) RAND_MAX, (double) rand() / (float) RAND_MAX, (double) rand() / (float) RAND_MAX};
	}
	t_object	**ps = malloc(TEST_SIZE * sizeof(int *));

	for (int i = 0; i < TEST_SIZE; i++)
		ps[i] = objs + i;
	stopwatch(3, 1, "idk");
	new_bvh(ps, TEST_SIZE, &bvh);
	stopwatch(3, 1 << 5, "yes");
	data.argv = argv;
	data.argc = argc;
	atexit(f);
	if (!parse_config_file(argc, argv, &data.scene))
		return (EXIT_FAILURE);
	create_mlx(&data.mlx_data);
	if (render(&data.mlx_data, &data.scene, WIDTH, HEIGHT))
		mlx_loop(data.mlx_data.mlx);
	mlx_terminate(data.mlx_data.mlx);
	return (EXIT_SUCCESS);
}
