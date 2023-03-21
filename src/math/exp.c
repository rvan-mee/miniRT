/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 22:54:19 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/21 22:54:19 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
#include <math.h>

t_fvec	exp_fvec(t_fvec vec)
{
	return ((t_fvec){
		expf(vec[0]),
		expf(vec[1]),
		expf(vec[2])
	});
}
