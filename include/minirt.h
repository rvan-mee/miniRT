/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:24:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/29 18:39:28 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <dynarr.h>
# include <MLX42/MLX42.h>
# include <pthread.h>
# include <bmp.h>

# define WIDTH 1920
# define HEIGHT 1080

# define THREAD_C	12 // amount of threads
# define BLOCK_C	25 // don't set higher than 50

typedef float	t_fvec __attribute__ ((vector_size (4 * sizeof(float))));
typedef t_fvec	t_fmat[4];
typedef struct s_minirt	t_minirt;
typedef enum e_object_type {
	UNINITIALIZED = 0,
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
	COMMENT,
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
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
}	t_rgba;

typedef struct s_ambient {
	float	ratio;
}	t_ambient;

typedef struct s_camera {
	t_fvec	orientation;
	float	fov;
}	t_camera;

typedef struct s_light {
	float	brightness;
}	t_light;

typedef struct s_sphere {
	float	diameter;
	float	radius_sq;
}	t_sphere;

typedef struct s_triangle {
	t_fvec	vert[3];
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
	t_fvec	orientation;
}	t_plane;

typedef struct s_cylinder {
	t_fvec	top;
	t_fvec	orientation;
	float	diameter;
	float	height;
	float	radius_sq;
}	t_cylinder;

typedef struct s_object {
	t_fvec		coords;
	t_rgba		colour;
	union {
		t_ambient	ambient;
		t_camera	camera;
		t_light		light;
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_triangle	triangle;
	};
	t_obj_type	type;
}	t_object;

typedef struct s_cluster	t_cluster;
typedef struct s_bvh {
	t_object	*prims;
	t_cluster	*clusters;
	uint32_t	root;
	uint32_t	prim_size;
}	t_bvh;

typedef struct s_scene {
	t_object	camera;
	t_object	ambient;
	t_object	*lights;
	size_t		lights_len;
	t_object	*objects;
	size_t		objects_len;
	t_bvh		bvh;
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
	float		u;
	float		v;
}	t_hit;

typedef struct s_render_block
{
	size_t			start_pixels[2];
	size_t			end_pixels[2];
	size_t			size[2];
	t_object		camera;
	t_ray			**rays;
}	t_render;

typedef struct s_jobs {
	void			(*job)(t_minirt *, void *);
	void			*job_param;
	struct s_jobs	*next_job;
}	t_jobs;

typedef struct s_threading
{
	bool			quit;
	pthread_mutex_t	quit_lock;
	pthread_t		threads[THREAD_C];
	size_t			created_threads;
	t_jobs			*job_lst;
	pthread_mutex_t	job_lock;
	sem_t			*print_lock;
}	t_threading;

typedef struct s_texture
{
	t_bmp		*bmp;
}	t_texture;

typedef struct s_minirt {
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
	char		**argv;
	int			argc;
	size_t		width;
	size_t		height;
	t_threading	thread;
	t_texture	texture;
}	t_minirt;

typedef struct s_aabb {
	t_fvec	min;
	t_fvec	max;
}	t_aabb;

void	start_render(t_minirt *data, void *func_data);

t_aabb	calc_bounds(t_object *obj);

/**
 * Combine two axis aligned bounding boxes
 */
t_aabb	aabb_combine(t_aabb a, t_aabb b);


/**
 * Calculate surface area of a bounding box
 */
float	sa(t_aabb aabb);

/**
 * Calculate surface area of two combined bounding boxes
 */
float	combo_sa(t_aabb a, t_aabb b);

#endif
