/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_orientation.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:41:36 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/15 20:41:36 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>
#include <math.h>

static void	identity_matrix(t_fmat matrix)
{
	const t_fmat	identity = {
			(t_fvec){1.0f, 0.0f, 0.0f, 0.0f},
			(t_fvec){0.0f, 1.0f, 0.0f, 0.0f},
			(t_fvec){0.0f, 0.0f, 1.0f, 0.0f},
			(t_fvec){0.0f, 0.0f, 0.0f, 1.0f}
	};

	matrix[0] = identity[0];
	matrix[1] = identity[1];
	matrix[2] = identity[2];
	matrix[3] = identity[3];
}

static void	axis_angle_to_matrix(t_fmat dst, t_fvec a, float angle)
{
	const float	c = cosf(angle);
	const float	s = sinf(angle);
	const float	t = 1 - c;

	dst[0][0] = c + a[X] * a[X] * t;
	dst[0][1] = a[X] * a[Y] * t - a[Z] * s;
	dst[0][2] = a[X] * a[Z] * t + a[Y] * s;
	dst[1][0] = a[Y] * a[X] * t + a[Z] * s;
	dst[1][1] = c + a[Y] * a[Y] * t;
	dst[1][2] = a[Y] * a[Z] * t - a[X] * s;
	dst[2][0] = a[Z] * a[X] * t - a[Y] * s;
	dst[2][1] = a[Z] * a[Y] * t + a[X] * s;
	dst[2][2] = c + a[Z] * a[Z] * t;
}

static void	build_rotation_matrix(t_fmat dst, t_fvec cam_orientation)
{
	static const t_fvec	z_unit = {0, 0, 1};
	float				angle;
	t_fvec				axis;
	float				axis_len;

	angle = acosf(dot_product(cam_orientation, z_unit));
	if (angle == 0.0)
		return (identity_matrix(dst));
	axis = cross_product(cam_orientation, z_unit);
	axis_len = sqrtf(axis[X] * axis[X] + axis[Y] * axis[Y] + axis[Z] * axis[Z]);
	axis /= axis_len;
	axis_angle_to_matrix(dst, axis, angle);
}

static void	rotate_vector(t_fvec *vecp, t_fmat mat)
{
	const t_fvec	vec = *vecp;

	*vecp = ((t_fvec){
			vec[X] * mat[X][0] +
			vec[Y] * mat[X][1] +
			vec[Z] * mat[X][2],
			vec[X] * mat[Y][0] +
			vec[Y] * mat[Y][1] +
			vec[Z] * mat[Y][2],
			vec[X] * mat[Z][0] +
			vec[Y] * mat[Z][1] +
			vec[Z] * mat[Z][2]
	});
}

void	normalize_orientation(t_scene *scene)
{
	t_object	*obj;
	t_fmat		matrix;
	size_t		i;

	build_rotation_matrix(matrix, scene->camera.camera.orientation);
	rotate_vector(&scene->camera.camera.orientation, matrix);
	i = scene->lights_len;
	while (i--)
		rotate_vector(&scene->lights[i].coords, matrix);
	i = scene->objects_len;
	while (i--)
	{
		obj = scene->objects + i;
		if (obj->type == PLANE)
		{
			rotate_vector(&obj->plane.coords, matrix);
			rotate_vector(&obj->plane.orientation, matrix);
		}
		else if (obj->type == CYLINDER)
		{
			rotate_vector(&obj->cylinder.coords, matrix);
			rotate_vector(&obj->cylinder.orientation, matrix);
		}
		else if (obj->type == SPHERE)
			rotate_vector(&obj->sphere.coords, matrix);
	}
}