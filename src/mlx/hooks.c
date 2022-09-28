/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 12:12:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/28 12:43:21 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <ft_math.h>
#include <parse.h>
#include <bmp.h>
#include <stdlib.h>

#define STEPS 2.5f
#define ROT_AMOUNT 15
#define DEG 0.0174533

static void	reload_scene(t_minirt *data)
{
	free(data->scene.lights);
	free(data->scene.objects);
	printf("reloading file\n");
	if (!parse_config_file(data->argc, data->argv, &data->scene))
		return ;
	normalize(&data->scene);
	if (!render(&data->mlx_data, &data->scene, WIDTH, HEIGHT))
		mlx_close_window(data->mlx_data.mlx);
	printf("done rendering file\n");
}

static void	move_cam(t_minirt *data, enum keys key)
{
	t_camera *cam;

	cam = &data->scene.camera.camera;
	if (key == MLX_KEY_W)
		cam->coords[Z] += STEPS;
	else if (key == MLX_KEY_A)
		cam->coords[X] -= STEPS;
	else if (key == MLX_KEY_S)
		cam->coords[Z] -= STEPS;
	else if (key == MLX_KEY_D)
		cam->coords[X] += STEPS;
	normalize(&data->scene);
	if (!render(&data->mlx_data, &data->scene, WIDTH, HEIGHT))
		mlx_close_window(data->mlx_data.mlx);
}

static t_fvec	rodrigues_rotation(t_fvec old_rotation, t_fvec axis, float angle)
{
	t_fvec	new_rotation;

	new_rotation = old_rotation * cosf(angle) \
	+ cross_product(axis, old_rotation) * sinf(angle) \
	+ axis * dot_product(axis, old_rotation) * (1 - cosf(angle));
	return (new_rotation);
}

static void	rotate_cam(t_minirt *data, enum keys key)
{
	const t_fvec	rot_y = {1, 0, 0, 0};
	const t_fvec	rot_x = {0, 1, 0, 0};
	t_camera		*cam;

	cam = &data->scene.camera.camera;
	printf("changing camera rotation\n");
	if (key == MLX_KEY_UP)
		cam->orientation = rodrigues_rotation(cam->orientation, -rot_y, DEG * ROT_AMOUNT);
	else if (key == MLX_KEY_DOWN)
		cam->orientation = rodrigues_rotation(cam->orientation, rot_y, DEG * ROT_AMOUNT);
	else if (key == MLX_KEY_LEFT)
		cam->orientation = rodrigues_rotation(cam->orientation, -rot_x, DEG * ROT_AMOUNT);
	else if (key == MLX_KEY_RIGHT)
		cam->orientation = rodrigues_rotation(cam->orientation, rot_x, DEG * ROT_AMOUNT);
	normalize(&data->scene);
	if (!render(&data->mlx_data, &data->scene, WIDTH, HEIGHT))
		mlx_close_window(data->mlx_data.mlx);
	printf("done rendering\n");
}

void	keyhook(mlx_key_data_t keydata, t_minirt *data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx_data.mlx);
	else if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		create_bmp(data->mlx_data.img);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		reload_scene(data);
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A\
			|| keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D)\
			&& keydata.action == MLX_PRESS)
		move_cam(data, keydata.key);
	else if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN\
			|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)\
			&& keydata.action == MLX_PRESS)
		rotate_cam(data, keydata.key);
}
