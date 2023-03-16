/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 12:12:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/03/13 16:12:23 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <mlx.h>
#include <render.h>

static void	create_picture(t_minirt *data, enum keys key)
{
	(void)key;
	create_bmp(data->img);
}

// MLX_KEY_MENU is the last var inside the enum
static void	(*g_hook_func[MLX_KEY_MENU + 1])(t_minirt *, enum keys) = {\
	[MLX_KEY_R] = reload_scene,							\
	[MLX_KEY_W] = move_cam,								\
	[MLX_KEY_A] = move_cam,								\
	[MLX_KEY_S] = move_cam,								\
	[MLX_KEY_D] = move_cam,								\
	[MLX_KEY_Q] = move_cam,								\
	[MLX_KEY_E] = move_cam,								\
	[MLX_KEY_P] = create_picture,						\
	[MLX_KEY_UP] = rotate_cam,							\
	[MLX_KEY_DOWN] = rotate_cam,						\
	[MLX_KEY_LEFT] = rotate_cam,						\
	[MLX_KEY_RIGHT] = rotate_cam,						\
	[MLX_KEY_Z] = change_exposure,						\
	[MLX_KEY_X] = change_exposure,						\
	[MLX_KEY_C] = print_camera_attributes,				\
	[MLX_KEY_LEFT_BRACKET] = change_fov,				\
	[MLX_KEY_RIGHT_BRACKET] = change_fov,				\
};

void	keyhook(mlx_key_data_t keydata, t_minirt *data)
{
	if (keydata.action == MLX_PRESS && g_hook_func[keydata.key])
	{
		stop_working(data->thread, true);
		clear_job_lst(data->thread);
		wait_till_done(data->thread);
		g_hook_func[keydata.key](data, keydata.key);
	}
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		quit_working(data->thread);
		clear_job_lst(data->thread);
		mlx_close_window(data->mlx);
	}
}

void	mouse_hook(mouse_key_t type, action_t action, modifier_key_t mod, t_minirt *data)
{
	(void) type, (void) mod;
	if (action != MLX_PRESS)
		return;
	t_hit		hit;
	t_dynarr	hits = {&hit, sizeof(t_hit), 1, 0};
	int32_t		x, y;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	size_t		screen[2] = {x, y};
	t_ray		ray = get_cam_ray(&data->scene->camera, screen[X], screen[Y]);
	if (trace(data->scene, &ray, screen, &hits))
	{
		printf("hit at (%lu,%lu) ==> (%f, %f, %f) == objects[%lu]\n", screen[X], screen[Y],
			   hit.hit[X], hit.hit[Y], hit.hit[Z], hit.object - data->scene->objects);
	}
}
