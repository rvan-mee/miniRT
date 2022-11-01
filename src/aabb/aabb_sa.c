/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aabb_sa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:00:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/01 15:00:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>

float	aabb_sa(t_aabb a, t_aabb b)
{
	const t_aabb	combined = aabb_combine(a, b);
	const t_fvec	size = combined.max - combined.min;

	return (dot_product(size, size));
}
