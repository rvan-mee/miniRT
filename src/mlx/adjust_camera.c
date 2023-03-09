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
#include "ft_math.h"

#define STEPS	0.1f

static float	adjust_step_for_size(t_bvh *bvh)
{
	const t_aabb	plane_bounds = {
		{-10000, -10000, -10000},
		{10000, 10000, 10000}
	};
	t_cluster		*cluster;
	t_fvec			delta;

	cluster = bvh->clusters + bvh->root;
	while (true)
	{
		if (ft_memcmp(&cluster->aabb, &plane_bounds, sizeof(t_aabb)) != 0)
		{
			delta = cluster->aabb.max - cluster->aabb.min;
			return (sqrtf(powf(delta[X], 2.f) + powf(delta[Y], 2.f)) * STEPS);
		}
		if (cluster->len == 1)
			return (STEPS);
		if (bvh->clusters[cluster->l].len > 1)
			cluster = bvh->clusters + cluster->l;
		else
			cluster = bvh->clusters + cluster->r;
	}

}

void	move_cam(t_minirt *data, enum keys key)
{
	const float	step = adjust_step_for_size(&data->scene.bvh);
	t_object *cam;

	cam = &data->scene.camera;
	if (key == MLX_KEY_W)
		cam->coords += step * cam->camera.orientation;
	else if (key == MLX_KEY_S)
		cam->coords -= step * cam->camera.orientation;
	else if (key == MLX_KEY_A)
		cam->coords -= step * cam->camera.u;
	else if (key == MLX_KEY_D)
		cam->coords += step * cam->camera.u;
	else if (key == MLX_KEY_Q)
		cam->coords -= step * cam->camera.v;
	else if (key == MLX_KEY_E)
		cam->coords += step * cam->camera.v;
	reset_work(data);
}


static t_fvec	rodrigues_rotation(t_fvec old_rot, t_fvec axis, float angle)
{
	t_fvec	new_rotation;

	new_rotation = old_rot * cosf(angle);
	new_rotation += cross_product(axis, old_rot) * sinf(angle);
	new_rotation += axis * dot_product(axis, old_rot) * (1 - cosf(angle));
	return (new_rotation);
}

void	calc_ray_info(t_camera *cam, float w, float h);
// rotates along an axis (x or y)
void	rotate_cam(t_minirt *data, enum keys key)
{
	const float	amount = M_PI / 6;
	t_camera	*cam;
	t_fvec		axis;

	cam = &data->scene.camera.camera;
	if (key == MLX_KEY_UP || key == MLX_KEY_DOWN)
		axis = cam->u;
	else
		axis = cam->v;
	if (key == MLX_KEY_UP || key == MLX_KEY_LEFT)
		axis = -axis;
	cam->orientation = rodrigues_rotation(cam->orientation, axis, amount);
	calc_ray_info(cam, WIDTH, HEIGHT);
	reset_work(data);
}

void	change_exposure(t_minirt *data, enum keys key)
{
	const bool	decrement = key == MLX_KEY_Z;

	if (decrement)
		data->scene.camera.camera.exposure -= 0.5f;
	else
		data->scene.camera.camera.exposure += 0.5f;
	printf("Changed camera exposure to %f\n", data->scene.camera.camera.exposure);
	reset_work(data);
}
