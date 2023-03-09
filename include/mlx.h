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
void	mouse_hook(mouse_key_t type, action_t action, modifier_key_t mod, t_minirt *data);
bool	create_mlx(t_minirt *data);

void	reload_scene(t_minirt *data, enum keys key);

#endif
