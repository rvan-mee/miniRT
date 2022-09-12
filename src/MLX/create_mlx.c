/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_mlx.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:32:16 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 16:24:02 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <miniRT.h>
#include <stdlib.h>

void	create_mlx(mlx_t **mlx, mlx_image_t **img)
{
	*mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!*mlx)
		exit(EXIT_FAILURE);
	*img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (!*img || mlx_image_to_window(*mlx, *img, 0, 0) == -1)
	{
		mlx_terminate(*mlx);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(*mlx, &keyhook, *img);
}
