/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_math.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:39:55 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/22 15:57:21 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H
# include <minirt.h>
# include <stdbool.h>

# define FLOAT_EPSILON	0.00000001f

typedef struct s_quadratic {
	float	a;
	float	b;
	float	c;
}	t_quadratic;

t_fvec	normalize_vector(t_fvec vec);
float	dot_product(t_fvec a, t_fvec b);
t_fvec	cross_product(t_fvec a, t_fvec b);
t_fvec	exp_fvec(t_fvec vec);
t_fvec	min_vec(t_fvec a, t_fvec b);
t_fvec	max_vec(t_fvec a, t_fvec b);
float	min_val(t_fvec v);
float	max_val(t_fvec v);

void	identity_matrix(t_fmat matrix);
t_fvec	mult_vec_mat(t_fvec vec, t_fmat mat);

bool	solve_quadratic(t_quadratic *quadratic, float t[2]);

/**
 * Reflect about a normal
 *
 * @param in The "incoming" unit vector. This should be pointing in the same
 *   direction of the normal (normal dot in should be positive)
 * @param normal The normal unit vector we want to reflect around.
 * @return A unit vector, with the same angle difference with the normal as
 *   the in vector
 */
t_fvec	reflect(t_fvec in, t_fvec normal);
t_fvec	refract(t_fvec in, t_fvec normal, float exiting, float entering);

static inline
float	rt_minf(float a, float b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

static inline
float	rt_maxf(float a, float b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

static inline
float	rt_absf(float f)
{
	if (f < 0)
		return (-f);
	else
		return (f);
}

#endif