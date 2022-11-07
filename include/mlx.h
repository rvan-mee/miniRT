/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:32:46 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/20 18:28:22 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# include <MLX42/MLX42.h>
# include <minirt.h>

void	keyhook(mlx_key_data_t keydata, t_minirt *data);
void	create_mlx(t_minirt *data);

#endif
