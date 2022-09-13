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

bool	parse_float(float f, float min, float max)
{
	if (f < min || f > max)
		return (false);
	return (true);
}

bool	parse_vector(char *line, char **end, t_fvec *vector, bool normalized)
{
	(*vector)[X] = ft_strtof(line, &line);
	if (line[0] != ',' || (!ft_isdigit(line[1]) && line[1] != '-'))
		return (false);
	line++;
	(*vector)[Y] = ft_strtof(line, &line);
	if (line[0] != ',' || (!ft_isdigit(line[1]) && line[1] != '-'))
		return (false);
	line++;
	(*vector)[Z] = ft_strtof(line, &line);
	*end = line;
	if (normalized && (!parse_float((*vector)[X], -1.0f, 1.0f) \
	|| !parse_float((*vector)[Y], -1.0f, 1.0f) \
	|| !parse_float((*vector)[Z], -1.0f, 1.0f)))
		return (false);
	return (true);
}
