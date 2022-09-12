/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:32:46 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 17:20:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# include <MLX42/MLX42.h>
# include <miniRT.h>

void	keyhook(mlx_key_data_t keydata, t_mlx_data *mlx_data);
void	create_mlx(t_mlx_data *mlx_data);

#endif
