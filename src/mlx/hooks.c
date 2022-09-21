/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 12:12:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 17:20:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <bmp.h>

void	keyhook(mlx_key_data_t keydata, t_mlx_data *mlx_data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx_data->mlx);
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		create_bmp(mlx_data->img);
}
