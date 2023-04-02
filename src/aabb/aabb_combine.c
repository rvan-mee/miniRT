/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aabb_combine.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:00:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/01 15:00:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <bvh.h>
#include <ft_math.h>

inline t_aabb	aabb_combine(const t_aabb a, const t_aabb b)
{
	return ((t_aabb){
		.min = min_vec(a.min, b.min),
		.max = max_vec(a.max, b.max)
	});
}

inline t_aabb	aabb_grow(const t_aabb bounds, const t_fvec point)
{
	return ((t_aabb){
		.min = min_vec(bounds.min, point),
		.max = max_vec(bounds.max, point)
	});
}
