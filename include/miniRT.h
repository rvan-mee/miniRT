/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:24:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/12 17:20:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdint.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef double	t_dvec __attribute__ ((vector_size (4 * sizeof(double))));

typedef enum e_object_type {
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef union u_rgba {
	uint32_t	colour;
	struct {
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
}	t_rgba;

/*
 * NOTES:
 *
 * Orientation is apparently not a unit vector - subject gives 0,0,0 as valid example.
 * Someone in slack said they interpreted this as rotation around axis (1.0 == 1 PI rad)
 *
 * Does [0.0,1.0] mean step is 0.1? Or could it also be 0.975234? No clue, but guess float is enough
 */

typedef struct s_mlx_content {
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_mlx_data;

typedef struct s_ambient {
	float	ratio; // [0.0, 1.0]
	t_rgba	colour;
}	t_ambient;

typedef struct s_camera {
	t_dvec	coords;
	t_dvec	orientation; // see notes
	uint8_t	fov; // [0, 180]
}	t_camera;

typedef struct s_light {
	t_dvec	coords;
	float	brightness; // [0.0, 1.0]
	t_rgba	colour; // unused in mandatory
}	t_light;

typedef struct s_sphere {
	t_dvec	coords;
	float	diameter;
	t_rgba	colour;
}	t_sphere;

typedef struct s_plane {
	t_dvec	coords;
	t_dvec	orientation; // see notes
	t_rgba	colour;
}	t_plane;

typedef struct s_cylinder {
	t_dvec	coords;
	t_dvec	orientation; // see notes
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

#endif
