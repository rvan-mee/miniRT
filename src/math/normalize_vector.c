/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:56:53 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/21 15:56:53 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

t_fvec	normalize_vector(t_fvec vec)
{
	float	magnitude;

	magnitude = sqrtf(vec[X] * vec[X] + vec[Y] * vec[Y] + vec[Z] * vec[Z]);
	return (vec / magnitude);
}
