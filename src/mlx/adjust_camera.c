/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   adjust_camera.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 11:50:57 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/09 11:50:57 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <bvh.h>
#include <thread.h>
#include <math.h>
#include "libft.h"

#define STEPS	0.05f

void	move_cam(t_minirt *data, enum keys key)
{
	const float	step = STEPS * data->scene.scale;
	t_object *cam;

	cam = &data->scene.camera;
	if (key == MLX_KEY_W)
		cam->coords += step * cam->camera.rotated;
	else if (key == MLX_KEY_S)
		cam->coords -= step * cam->camera.rotated;
	else if (key == MLX_KEY_A)
		cam->coords -= step * cam->camera.u;
	else if (key == MLX_KEY_D)
		cam->coords += step * cam->camera.u;
	else if (key == MLX_KEY_Q)
		cam->coords[Y] -= step;
	else if (key == MLX_KEY_E)
		cam->coords[Y] += step;
	reset_work(data);
}

void	calc_ray_info(t_camera *cam);
void	rotate_cam(t_minirt *data, enum keys key)
{
	float		amount;
	t_camera	*cam;
	uint8_t		axis;

	cam = &data->scene.camera.camera;
	amount = M_PI / 12;
	axis = (key == MLX_KEY_UP || key == MLX_KEY_DOWN);
	if (key == MLX_KEY_UP || key == MLX_KEY_LEFT)
		amount = -amount;
	if (axis)
		if ((amount < 0 && cam->rotation[axis] == (float) -M_PI) || \
			(amount > 0 && cam->rotation[axis] == (float) M_PI))
			return;
	cam->rotation[axis] += amount;
	if (cam->rotation[axis] < -M_PI)
		cam->rotation[axis] += (float)(2 * M_PI);
	else if (cam->rotation[axis] > M_PI)
		cam->rotation[axis] -= (float)(2 * M_PI);
	calc_ray_info(cam);
	reset_work(data);
}

void	change_exposure(t_minirt *data, enum keys key)
{
	const bool	increase_effect = key == MLX_KEY_X;
	t_camera	 *cam;
	float		amount;

	cam = &data->scene.camera.camera;
	if (increase_effect)
		amount = cam->exposure / 9.0f;
	else
		amount = cam->exposure / -10.0f;
	cam->exposure += amount;
	printf("Changed camera exposure to %f\n", cam->exposure);
	reset_work(data);
}
