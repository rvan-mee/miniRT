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
#include <render.h>

float	get_ray_bias(t_fvec normal, t_fvec dir)
{
	return (rt_maxf(0.05f * (1.0f - rt_absf(dot_product(normal, dir))), 0.005f));
}

t_ray	get_biased_ray(t_fvec origin, t_fvec direction, t_fvec normal)
{
	const float	bias = get_ray_bias(normal, direction);

	return ((t_ray){
		.origin = origin + direction * bias,
		.direction = direction
	});
}
