/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:32:46 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/03/13 16:11:42 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# include <MLX42/MLX42.h>

typedef struct s_minirt	t_minirt;

void	keyhook(mlx_key_data_t keydata, t_minirt *data);
void	mouse_hook(mouse_key_t t, action_t a, modifier_key_t m, t_minirt *data);
bool	create_mlx(t_minirt *data);

void	reload_scene(t_minirt *data, enum keys key);
void	move_cam(t_minirt *data, enum keys key);
void	rotate_cam(t_minirt *data, enum keys key);
void	change_exposure(t_minirt *data, enum keys key);
void	change_fov(t_minirt *data, enum keys key);
void	print_camera_attributes(t_minirt *data, enum keys key);

#endif
