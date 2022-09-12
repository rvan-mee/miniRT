/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:32:46 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 16:22:40 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# include "MLX42/MLX42.h"

void	keyhook(mlx_key_data_t keydata, void *param);
void	create_mlx(mlx_t **mlx, mlx_image_t **img);

#endif
