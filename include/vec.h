/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:39:55 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/15 20:39:55 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H
# include <minirt.h>

float	dot_product(t_fvec a, t_fvec b);
t_fvec	cross_product(t_fvec a, t_fvec b);

#endif