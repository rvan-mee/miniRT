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

# include <stddef.h>
# include <MLX42/MLX42.h>

# define WIDTH 1920
# define HEIGHT 1080

# ifndef THREAD_C
#  define THREAD_C	8 // amount of threads
# endif

# ifndef USE_BVH
#  define USE_BVH	1
# endif

# ifndef USE_SMOOTH_SHADING
#  define USE_SMOOTH_SHADING 0
# endif

typedef float				t_fvec \
__attribute__ ((vector_size (4 * sizeof(float))));

typedef t_fvec				t_fmat[4];
typedef struct s_minirt		t_minirt;
typedef struct s_object		t_object;
typedef struct s_scene		t_scene;
typedef struct s_threading	t_threading;

enum e_axis {
	X,
	Y,
	Z
};

typedef struct s_minirt {
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	char		**argv;
	int			argc;
	size_t		width;
	size_t		height;
	t_threading	*thread;
}	t_minirt;

bool	init_render_data(t_minirt *data);

#endif
