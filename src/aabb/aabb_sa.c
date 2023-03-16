/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   combo_sa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:00:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/01 15:00:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <bvh.h>

float	sa(t_aabb aabb)
{
	const t_fvec	size = aabb.max - aabb.min;

	return (size[X] * size[Y] + size[X] * size[Z] + size[Y] * size[Z]);
}

float	combo_sa(t_aabb a, t_aabb b)
{
	const t_aabb	combined = aabb_combine(a, b);
	const t_fvec	size = combined.max - combined.min;

	return (size[X] * size[Y] + size[X] * size[Z] + size[Y] * size[Z]);
}
