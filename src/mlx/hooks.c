/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 12:12:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/12 14:33:24 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <ft_math.h>
#include <parse.h>
#include <bmp.h>
#include <stdlib.h>

#define STEPS 5.0f
#define ROT_AMOUNT 15
#define DEG 0.0174533

static void	reload_scene(t_minirt *data, enum keys key)
{
	(void) key;
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
	t_camera	*cam;

	printf("changing camera position\n");
	cam = &data->scene.camera.camera;
	if (key == MLX_KEY_W)
		cam->coords[Z] += STEPS;
	else if (key == MLX_KEY_A)
		cam->coords[X] -= STEPS;
	else if (key == MLX_KEY_S)
		cam->coords[Z] -= STEPS;
	else if (key == MLX_KEY_D)
		cam->coords[X] += STEPS;
	else if (key == MLX_KEY_Q)
		cam->coords[Y] -= STEPS;
	else if (key == MLX_KEY_E)
		cam->coords[Y] += STEPS;
	normalize(&data->scene);
	if (!render(&data->mlx_data, &data->scene, WIDTH, HEIGHT))
		mlx_close_window(data->mlx_data.mlx);
	printf("done rendering\n");
}

static t_fvec	rodrigues_rotation(t_fvec old_rot, t_fvec axis, float angle)
{
	t_fvec	new_rotation;

	new_rotation = old_rot * cosf(angle) \
	+ cross_product(axis, old_rot) * sinf(angle) \
	+ axis * dot_product(axis, old_rot) * (1 - cosf(angle));
	return (new_rotation);
}

// rotates along an axis (x or y)
static void	rotate_cam(t_minirt *data, enum keys key)
{
	const t_fvec	rot_x = {1, 0, 0, 0};
	const t_fvec	rot_y = {0, 1, 0, 0};
	const float		amount = DEG * ROT_AMOUNT;
	t_fvec			*orientation;

	printf("changing camera rotation\n");
	orientation = &data->scene.camera.camera.orientation;
	if (key == MLX_KEY_UP)
		*orientation = rodrigues_rotation(*orientation, -rot_x, amount);
	else if (key == MLX_KEY_DOWN)
		*orientation = rodrigues_rotation(*orientation, rot_x, amount);
	else if (key == MLX_KEY_LEFT)
		*orientation = rodrigues_rotation(*orientation, -rot_y, amount);
	else if (key == MLX_KEY_RIGHT)
		*orientation = rodrigues_rotation(*orientation, rot_y, amount);
	normalize(&data->scene);
	if (!render(&data->mlx_data, &data->scene, WIDTH, HEIGHT))
		mlx_close_window(data->mlx_data.mlx);
	printf("done rendering\n");
}

// MLX_KEY_MENU is the last var inside the enum
static void	(*g_hook_func[])(t_minirt *, enum keys) = {\
	[MLX_KEY_R] = reload_scene,							\
	[MLX_KEY_W] = move_cam,								\
	[MLX_KEY_A] = move_cam,								\
	[MLX_KEY_S] = move_cam,								\
	[MLX_KEY_D] = move_cam,								\
	[MLX_KEY_Q] = move_cam,								\
	[MLX_KEY_E] = move_cam,								\
	[MLX_KEY_UP] = rotate_cam,							\
	[MLX_KEY_DOWN] = rotate_cam,						\
	[MLX_KEY_LEFT] = rotate_cam,						\
	[MLX_KEY_RIGHT] = rotate_cam,						\
	[MLX_KEY_MENU] = NULL,								\
};

void	keyhook(mlx_key_data_t keydata, t_minirt *data)
{
	if (keydata.action == MLX_PRESS && g_hook_func[keydata.key])
		g_hook_func[keydata.key](data, keydata.key);
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx_data.mlx);
}
