/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 12:12:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 16:24:15 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <miniRT.h>
#include <bmp.h>
#include <stdlib.h>

void	keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS);
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		create_bmp(param);
}
