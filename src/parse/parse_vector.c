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
#include <miniRT.h>
#include <libft.h>

bool	parse_float(char **linep, float *dst, float min, float max)
{
	char	*end;

	*dst = ft_strtof(*linep, &end);
	if (*linep == end || !ft_isdigit(end[-1]))
		return (false);
	*linep = end;
	if (min == max)
		return (true);
	return (*dst >= min && *dst <= max);
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
	return (true);
}
