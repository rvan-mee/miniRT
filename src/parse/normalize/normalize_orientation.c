/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_orientation.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:41:36 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/12 14:08:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
#include <math.h>
#include <float.h>

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

// isnan = temp fix for weird cam movement
// config:	(C		0,-100,0 	0.70710678118,0.70710678118,0		120)
static void	build_rotation_matrix(t_fmat dst, t_fvec cam_orientation)
{
	static const t_fvec	z_unit = {0, 0, 1};
	float				angle;
	t_fvec				axis;

	angle = acosf(dot_product(cam_orientation, z_unit));
	if (angle == 0.0 || isnan(angle))
		return (identity_matrix(dst));
	if (fabs(angle - M_PI) < FLT_EPSILON * 128)
	{
		dst[0] = (t_fvec){-1.f, 0.0f, 0.0f};
		dst[1] = (t_fvec){0.0f, 1.f, 0.0f};
		dst[2] = (t_fvec){0.0f, 0.0f, -1.0f};
		return ;
	}
	axis = cross_product(cam_orientation, z_unit);
	axis = normalize_vector(axis);
	axis_angle_to_matrix(dst, axis, angle);
}

static void	rotate_vector(t_fvec *vecp, t_fmat mat)
{
	*vecp = mult_vec_mat(*vecp, mat);
}

static void	rotate_object(t_object *object, t_fmat matrix)
{
	if (object->type == PLANE)
	{
		rotate_vector(&object->plane.coords, matrix);
		rotate_vector(&object->plane.orientation, matrix);
	}
	else if (object->type == CYLINDER)
	{
		rotate_vector(&object->cylinder.coords, matrix);
		rotate_vector(&object->cylinder.orientation, matrix);
		rotate_vector(&object->cylinder.top, matrix);
	}
	else if (object->type == SPHERE)
		rotate_vector(&object->sphere.coords, matrix);
	else if (object->type == TRIANGLE)
	{
		rotate_vector(&object->triangle.vert[0], matrix);
		rotate_vector(&object->triangle.vert[1], matrix);
		rotate_vector(&object->triangle.vert[2], matrix);
		rotate_vector(&object->triangle.v0v1, matrix);
		rotate_vector(&object->triangle.v0v2, matrix);
	}
}

void	normalize_orientation(t_scene *scene)
{
	t_fmat		matrix;
	size_t		i;

	build_rotation_matrix(matrix, scene->camera.camera.orientation);
	rotate_vector(&scene->camera.camera.orientation, matrix);
	i = scene->lights_len;
	while (i--)
		rotate_vector(&scene->lights[i].coords, matrix);
	i = scene->objects_len;
	while (i--)
		rotate_object(scene->objects + i, matrix);
}
