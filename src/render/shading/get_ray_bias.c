/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_ray_bias.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:39:52 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/13 16:39:52 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
#include <math.h>

float	get_ray_bias(t_fvec normal, t_fvec dir)
{
	return (fmaxf(0.05f * (1.0f - fabsf(dot_product(normal, dir))), 0.005f));
}
