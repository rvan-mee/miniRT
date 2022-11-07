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

#include <minirt.h>
#include <math.h>

t_aabb	aabb_combine(const t_aabb a, const t_aabb b)
{
	const t_fvec	amin = a.min;
	const t_fvec	bmin = b.min;
	const t_fvec	amax = a.max;
	const t_fvec	bmax = b.max;

	return ((t_aabb){
		.min = {
			fminf(amin[X], bmin[X]),
			fminf(amin[Y], bmin[Y]),
			fminf(amin[Z], bmin[Z])
		},
		.max = {
			fmaxf(amax[X], bmax[X]),
			fmaxf(amax[Y], bmax[Y]),
			fmaxf(amax[Z], bmax[Z])
		}
	});
}
