/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   refract.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 19:41:46 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/21 19:41:46 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
#include <math.h>

t_fvec	refract(t_fvec in, t_fvec normal, float exiting, float entering)
{
	const float	cos_t = -dot_product(in, normal);
	const float	mu = exiting / entering;
	t_fvec		dir;

	dir = mu * in;
	dir += normal * (mu * cos_t - sqrtf(1 - mu * mu * (1 - cos_t * cos_t)));
	return (normalize_vector(dir));
}
