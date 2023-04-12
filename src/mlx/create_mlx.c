/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_mlx.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:32:16 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/04/12 12:48:21 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <minirt.h>
#include <unistd.h>
#include <stdio.h>
#define MLX_INIT_FAIL "Failed to initialize mlx\n"
#define MLX_IMG_FAIL "Failed to create an image\n\n"
#define MLX_WINDOW_FAIL "Failed to set the image to the window\n"

void	quit_working(t_threading *thread);

static void	close_hook(t_threading **threadp)
{
	if (*threadp)
		quit_working(*threadp);
}

bool	create_mlx(t_minirt	*data)
{
	data->mlx = mlx_init(data->width, data->height, "miniRT", false);
	if (!data->mlx)
		return (dprintf(STDERR_FILENO, MLX_INIT_FAIL), false);
	mlx_set_window_pos(data->mlx, 0, 0);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img)
		return (dprintf(STDERR_FILENO, MLX_IMG_FAIL), false);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
		return (dprintf(STDERR_FILENO, MLX_WINDOW_FAIL), false);
	mlx_key_hook(data->mlx, (mlx_keyfunc)keyhook, data);
	mlx_mouse_hook(data->mlx, (mlx_mousefunc)mouse_hook, data);
	mlx_close_hook(data->mlx, (mlx_closefunc) close_hook, &data->thread);
	return (true);
}
