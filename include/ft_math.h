/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_math.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:39:55 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/15 20:39:55 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H
# include <minirt.h>

float	dot_product(t_fvec a, t_fvec b);
t_fvec	cross_product(t_fvec a, t_fvec b);

void	identity_matrix(t_fmat matrix);
t_fvec	mult_vec_mat(t_fvec vec, t_fmat mat);

#endif