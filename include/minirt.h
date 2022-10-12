/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:24:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/11 19:57:05 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>

# define WIDTH 500
# define HEIGHT 500

typedef float	t_fvec __attribute__ ((vector_size (4 * sizeof(float))));
typedef t_fvec	t_fmat[4];

typedef enum e_object_type {
	UNINITIALIZED = 0,
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
	END
}	t_obj_type;

enum e_axis {
	X,
	Y,
	Z
};

typedef union u_rgba {
	uint32_t	rgba;
	struct {
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	};
}	t_rgba;

typedef struct s_mlx_content {
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_mlx_data;

typedef struct s_ambient {
	float	ratio;
	t_rgba	colour;
}	t_ambient;

typedef struct s_camera {
	t_fvec	coords;
	t_fvec	orientation;
	float	fov;
}	t_camera;

typedef struct s_light {
	t_fvec	coords;
	float	brightness;
	t_rgba	colour;
}	t_light;

typedef struct s_sphere {
	t_fvec	coords;
	float	diameter;
	float	radius_sq;
	t_rgba	colour;
}	t_sphere;

typedef struct s_triangle {
	t_fvec	vert[3];
	t_rgba	colour;
	t_fvec	v0v1;
	t_fvec	v0v2;
}	t_triangle;

/**
 * A infinitely big plane (not aero)
 *
 * `orientation' is the normal of the planes' surface. This means that checking
 * for collision is pretty easy; if a line is perpendicular to the normal, the
 * plane is not hit!
 */
typedef struct s_plane {
	t_fvec	coords;
	t_fvec	orientation;
	t_rgba	colour;
}	t_plane;

typedef struct s_cylinder {
	t_fvec	coords;
	t_fvec	top;
	t_fvec	orientation;
	float	diameter;
	float	height;
	float	radius_sq;
	t_rgba	colour;
}	t_cylinder;

typedef struct s_object {
	t_obj_type	type;
	union {
		t_ambient	ambient;
		t_camera	camera;
		t_light		light;
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_triangle	triangle;
	};
}	t_object;

typedef struct s_scene {
	t_object	camera;
	t_object	ambient;
	t_light		*lights;
	size_t		lights_len;
	t_object	*objects;
	size_t		objects_len;
}	t_scene;

typedef struct s_ray {
	t_fvec	origin;
	t_fvec	direction;
}	t_ray;

typedef struct s_hit {
	t_ray		ray;
	float		distance;
	t_fvec		hit;
	t_object	*object;
	t_fvec		normal;
	size_t		screen_x;
	size_t		screen_y;
}	t_hit;

typedef struct s_minirt {
	t_mlx_data	mlx_data;
	t_scene		scene;
	char		**argv;
	int			argc;
}	t_minirt;

bool	render(t_mlx_data *mlx, t_scene *scene, size_t width, size_t height);

#endif
