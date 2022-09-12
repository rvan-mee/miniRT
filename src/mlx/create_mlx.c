/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_mlx.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:32:16 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 17:20:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <miniRT.h>
#include <stdlib.h>

void	create_mlx(t_mlx_data *mlx_data)
{
	mlx_data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!mlx_data->mlx)
		exit(EXIT_FAILURE);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	if (!mlx_data->img \
		|| mlx_image_to_window(mlx_data->mlx, mlx_data->img, 0, 0) == -1)
	{
		mlx_terminate(mlx_data->mlx);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(mlx_data->mlx, (mlx_keyfunc)keyhook, mlx_data);
}
