/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 12:12:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/26 18:09:13 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <bmp.h>

void	keyhook(mlx_key_data_t keydata, t_mlx_data *mlx_data)
{
	int	mouse_x;
	int	mouse_y;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx_data->mlx);
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		create_bmp(mlx_data->img);
	if (keydata.key == MLX_KEY_C)
	{
		mlx_get_mouse_pos(mlx_data->mlx, &mouse_x, &mouse_y);
		printf("mouse coords x; %d y: %d\n", mouse_x, mouse_y);
	}
}
