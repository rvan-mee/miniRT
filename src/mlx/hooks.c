/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 12:12:27 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/04/12 15:12:49 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <mlx.h>
#include <render.h>
#define INFO_FORMAT "\thit at\n\t\
x=%d,y=%d: objects[%lu]\n\t\
dist=%f\n\thit=(%f, %f, %f)\n\t\
normal=(%f, %f, %f)\n\tbary=(%f, %f, %f)\n\t\
refractive idx=%f/%f (exiting/entering)\n"

// MLX_KEY_MENU is the last var inside the enum
static void	(*g_hook_func[MLX_KEY_MENU + 1])(t_minirt *, enum keys) = {\
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
	else if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		wait_till_done(data->thread);
		create_bmp(data->img);
	}
}

void	mouse_hook(mouse_key_t t, action_t a, modifier_key_t m, t_minirt *data)
{
	int32_t	mouse[2];
	t_hit	hit;
	float	refl_idx;
	t_scene	*scene;

	(void ) t, (void) m;
	if (a != MLX_PRESS)
		return ;
	scene = data->scene;
	mlx_get_mouse_pos(data->mlx, mouse + X, mouse + Y);
	hit.ray = get_cam_ray(&scene->camera, \
				(float) mouse[X] + 0.5f, (float) mouse[Y] + 0.5f);
	if (!trace(scene, &hit.ray, &hit))
		return ;
	if (hit.inside_ri == 1.0f && is_flag(hit.object->mat, REFRACT_IDX))
		refl_idx = hit.object->mat->opt_dens;
	else
		refl_idx = 1.0f;
	printf(INFO_FORMAT, mouse[X], mouse[Y], hit.object - scene->objects,
		hit.distance, hit.hit[X], hit.hit[Y], hit.hit[Z],
		hit.normal[X], hit.normal[Y], hit.normal[Z],
		hit.bary[X], hit.bary[Y], hit.bary[Z],
		hit.inside_ri, refl_idx);
}
