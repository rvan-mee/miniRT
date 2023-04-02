/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_float_rgb.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:28:45 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/14 13:26:11 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

bool	parse_float_rgb(char **linep, t_fvec *rgb)
{
	float	vals[3];
	char	*line;

	line = *linep;
	if (!parse_float(&line, &vals[0], 0, 1))
		return (false);
	skip_spaces(&line);
	if (!parse_float(&line, &vals[1], 0, 1))
		return (false);
	skip_spaces(&line);
	if (!parse_float(&line, &vals[2], 0, 1))
		return (false);
	skip_spaces(&line);
	if (*line)
		return (false);
	(*rgb)[0] = vals[0];
	(*rgb)[1] = vals[1];
	(*rgb)[2] = vals[2];
	*linep = line;
	return (true);
}
