/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_mlx.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:32:16 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/20 18:28:14 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <minirt.h>
#include <stdlib.h>
#include <libft.h>

void	create_mlx(t_minirt	*data)
{
	data->mlx = mlx_init(data->width, data->height, "miniRT", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	mlx_set_window_pos(data->mlx, 0, 0);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img \
		|| mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_terminate(data->mlx);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(data->mlx, (mlx_keyfunc)keyhook, data);
}
