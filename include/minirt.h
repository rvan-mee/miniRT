/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:24:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/13 16:07:58 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>

# define WIDTH 1920
# define HEIGHT 1080

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
	END
}	t_obj_type;

typedef enum e_fvec_type {
	X,
	Y,
	Z
}	t_fvec_type;

typedef union u_rgba {
	uint32_t	rgba;
	struct {
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
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
	t_rgba	colour;
}	t_sphere;

typedef struct s_plane {
	t_fvec	coords;
	t_fvec	orientation;
	t_rgba	colour;
}	t_plane;

typedef struct s_cylinder {
	t_fvec	coords;
	t_fvec	orientation;
	float	diameter;
	float	height;
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

struct s_ray {
	t_fvec	origine;
	t_fvec	direction;
};

#endif
