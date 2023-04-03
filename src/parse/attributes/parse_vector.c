/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vector.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 18:38:18 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/13 19:54:07 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <float.h>
#include <ft_math.h>

static bool	is_normalized(t_fvec vec)
{
	static const float	cutoff = FLT_EPSILON * 128;

	vec *= vec;
	return (rt_absf(vec[X] + vec[Y] + vec[Z] - 1.0f) < cutoff);
}

bool	parse_vector(char **linep, t_fvec *vector, bool normalized)
{
	char	*line;
	float	vals[3];
	float	min;
	float	max;

	line = *linep;
	min = 0;
	max = 0;
	if (normalized)
	{
		min = -1.0f;
		max = +1.0f;
	}
	if (!parse_float(&line, vals + X, min, max) || *line++ != ',')
		return (false);
	if (!parse_float(&line, vals + Y, min, max) || *line++ != ',')
		return (false);
	if (!parse_float(&line, vals + Z, min, max))
		return (false);
	*vector = (t_fvec){vals[X], vals[Y], vals[Z]};
	*linep = line;
	return (!normalized || is_normalized(*vector));
}
