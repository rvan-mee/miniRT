/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aabb_intersect.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:00:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/01 15:00:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <ft_math.h>
#define MIN	0
#define MAX	1

float	aabb_intersect(const t_aabb bounds, const t_ray *ray, t_fvec inv_dir)
{
	t_fvec	t[2];
	float	tlims[2];

	t[MIN] = (bounds.min - ray->origin) * inv_dir;
	t[MAX] = (bounds.max - ray->origin) * inv_dir;
	tlims[MIN] = max_val(min_vec(t[MIN], t[MAX]));
	tlims[MAX] = min_val(max_vec(t[MIN], t[MAX]));
	if (tlims[MAX] < 0.0 || tlims[MAX] < tlims[MIN])
		return (MISS);
	return (rt_maxf(tlims[MIN], 0.0f));
}
