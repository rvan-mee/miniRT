/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 19:12:37 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/19 19:12:37 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>

void	identity_matrix(t_fmat matrix)
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

t_fvec	mult_vec_mat(t_fvec vec, t_fmat mat)
{
	return ((t_fvec){
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
