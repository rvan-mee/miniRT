/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minmax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 02:23:51 by lsinke        #+#    #+#                 */
/*   Updated: 2023/04/01 02:23:51 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>

inline t_fvec	min_vec(t_fvec a, t_fvec b)
{
	t_fvec	ret;
	uint8_t	i;

	i = 0;
	while (i < 4)
	{
		if (a[i] <= b[i])
			ret[i] = a[i];
		else
			ret[i] = b[i];
		++i;
	}
	return (ret);
}

inline t_fvec	max_vec(t_fvec a, t_fvec b)
{
	t_fvec	ret;
	uint8_t	i;

	i = 0;
	while (i < 4)
	{
		if (a[i] >= b[i])
			ret[i] = a[i];
		else
			ret[i] = b[i];
		++i;
	}
	return (ret);
}

inline float	min_val(t_fvec v)
{
	return (rt_minf(rt_minf(v[0], v[1]), v[2]));
}

inline float	max_val(t_fvec v)
{
	return (rt_maxf(rt_maxf(v[0], v[1]), v[2]));
}
