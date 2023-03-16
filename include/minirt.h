/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:24:19 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/13 16:21:48 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42/MLX42.h>
# include <pthread.h>

# define WIDTH 1920
# define HEIGHT 1080

# ifndef THREAD_C
#  define THREAD_C	8 // amount of threads
# endif
# define BLOCK_C	25 // don't set higher than 50

#ifndef USE_BVH
# define USE_BVH	1
#endif

#ifndef USE_SMOOTH_SHADING
#  define USE_SMOOTH_SHADING 0
#endif

typedef float	t_fvec __attribute__ ((vector_size (4 * sizeof(float))));
typedef t_fvec	t_fmat[4];
typedef struct s_minirt	t_minirt;
typedef struct s_object	t_object;
typedef struct s_scene	t_scene;

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
	t_fvec		bary;
	float		refl;
}	t_hit;

typedef struct s_render_block
{
	size_t			start_pixels[2];
	size_t			end_pixels[2];
	size_t			size[2];
}	t_render;

typedef struct s_jobs {
	void			(*job)(t_minirt *, void *);
	void			*job_param;
	struct s_jobs	*next_job;
}	t_jobs;

typedef struct s_threading
{
	bool			quit;
	bool			stop;
	pthread_cond_t	stop_cond;
	size_t			threads_done;
	pthread_cond_t	done_cond;
	pthread_mutex_t	quit_lock;
	pthread_t		threads[THREAD_C];
	size_t			created_threads;
	t_jobs			*job_lst;
	pthread_mutex_t	job_lock;
	uint64_t		render_start;
}	t_threading;

typedef struct s_minirt {
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	char		**argv;
	int			argc;
	size_t		width;
	size_t		height;
	t_threading	thread;
}	t_minirt;


bool	init_render_data(t_minirt *data);

#endif
