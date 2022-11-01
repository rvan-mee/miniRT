/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:31:51 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/07 20:53:52 by rvan-mee      ########   odam.nl         */
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
	// mlx_t	*mlx;
	data.texture.bmp = parse_bmp("texture.bmp");
	// mlx = mlx_init(data.texture.bmp->width, data.texture.bmp->height, "test bmp", false);
	// mlx_image_t *img = mlx_new_image(mlx, data.texture.bmp->width, data.texture.bmp->height);
	// mlx_image_to_window(mlx, img, 0, 0);
	// t_rgba	rgb;
	// printf("image width: %d height: %d\n", data.texture.bmp->width, data.texture.bmp->height);
	// for (int32_t y = 0; y < data.texture.bmp->height; y++)
	// {
	// 	for (int32_t x = 0; x < data.texture.bmp->width; x++)
	// 	{
	// 		rgb.b = data.texture.bmp->data[(((data.texture.bmp->height - 1 - y) * data.texture.bmp->width + x) * 3)];
	// 		rgb.g = data.texture.bmp->data[(((data.texture.bmp->height - 1 - y) * data.texture.bmp->width + x) * 3) + 1];
	// 		rgb.r = data.texture.bmp->data[(((data.texture.bmp->height - 1 - y) * data.texture.bmp->width + x) * 3) + 2];
	// 		rgb.a = 0xFF;
	// 		mlx_put_pixel(img, x, y, rgb.rgba);
	// 	}
	// }
	// mlx_loop(mlx);
	atexit(f);
	if (!parse_config_file(argc, argv, &data.scene) || \
		!new_bvh(data.scene.objects, data.scene.objects_len, &data.scene.bvh))
		return (EXIT_FAILURE);
	create_mlx(&data);
	if (init_work_threads(&data))
	{
		mlx_loop(data.mlx);
		join_threads(&data);
	}
	mlx_terminate(data.mlx);
	free(data.texture.bmp->data);
	free(data.texture.bmp->name);
	return (EXIT_SUCCESS);
}
