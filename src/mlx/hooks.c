/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 12:12:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/09 20:00:12 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <ft_math.h>
#include <bmp.h>
#include <thread.h>
#include <mlx.h>
#include <render.h>

#define STEPS			0.5f
#define ROT_AMOUNT		15
#define DEG				0.0174533

static void	move_cam(t_minirt *data, enum keys key)
{
	t_object *cam;

	cam = &data->scene.camera;
	if (key == MLX_KEY_W)
		cam->coords += STEPS * cam->camera.orientation;
	else if (key == MLX_KEY_S)
		cam->coords -= STEPS * cam->camera.orientation;
	else if (key == MLX_KEY_A)
		cam->coords -= STEPS * cam->camera.u;
	else if (key == MLX_KEY_D)
		cam->coords += STEPS * cam->camera.u;
	else if (key == MLX_KEY_Q)
		cam->coords -= STEPS * cam->camera.v;
	else if (key == MLX_KEY_E)
		cam->coords += STEPS * cam->camera.v;
	reset_work(data);
}

static t_fvec	rodrigues_rotation(t_fvec old_rot, t_fvec axis, float angle)
{
	t_fvec	new_rotation;

	new_rotation = old_rot * cosf(angle) \
	+ cross_product(axis, old_rot) * sinf(angle) \
	+ axis * dot_product(axis, old_rot) * (1 - cosf(angle));
	return (new_rotation);
}

void	calc_ray_info(t_camera *cam, float w, float h);
// rotates along an axis (x or y)
static void	rotate_cam(t_minirt *data, enum keys key)
{
	const t_fvec	rot_x = data->scene.camera.camera.u;
	const t_fvec	rot_y = data->scene.camera.camera.v;
	const float		amount = DEG * ROT_AMOUNT;
	t_fvec			*orientation;

	orientation = &data->scene.camera.camera.orientation;
	if (key == MLX_KEY_UP)
		*orientation = rodrigues_rotation(*orientation, -rot_x, amount);
	else if (key == MLX_KEY_DOWN)
		*orientation = rodrigues_rotation(*orientation, rot_x, amount);
	else if (key == MLX_KEY_LEFT)
		*orientation = rodrigues_rotation(*orientation, -rot_y, amount);
	else if (key == MLX_KEY_RIGHT)
		*orientation = rodrigues_rotation(*orientation, rot_y, amount);
	calc_ray_info(&data->scene.camera.camera, WIDTH, HEIGHT);
	reset_work(data);
}

static void	create_picture(t_minirt *data, enum keys key)
{
	(void)key;
	create_bmp(data->img);
}

static void	change_exposure(t_minirt *data, enum keys key)
{
	const bool	decrement = key == MLX_KEY_Z;

	if (decrement)
		data->scene.camera.camera.exposure -= 0.5f;
	else
		data->scene.camera.camera.exposure += 0.5f;
	printf("Changed camera exposure to %f\n", data->scene.camera.camera.exposure);
	reset_work(data);
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
};

void	keyhook(mlx_key_data_t keydata, t_minirt *data)
{
	if (keydata.action == MLX_PRESS && g_hook_func[keydata.key])
	{
		stop_working(&data->thread, true);
		clear_job_lst(data);
		wait_till_done(data);
		g_hook_func[keydata.key](data, keydata.key);
	}
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		quit_working(data);
		clear_job_lst(data);
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
	t_ray		ray = get_cam_ray(&data->scene.camera, screen[X], screen[Y]);
	if (trace(&data->scene, &ray, screen, &hits))
	{
		printf("hit at (%lu,%lu) ==> (%f, %f, %f) == objects[%lu]\n", screen[X], screen[Y],
			   hit.hit[X], hit.hit[Y], hit.hit[Z], hit.object - data->scene.objects);
	}
}
