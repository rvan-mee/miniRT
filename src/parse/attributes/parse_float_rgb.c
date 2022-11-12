/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_float_rgb.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:28:45 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/12 17:46:47 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

bool	parse_float_rgb(char **linep, t_float_rgb *rgb)
{
	t_float_rgb	vals;
	char		*line;

	line = *linep;
	skip_spaces(&line);
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
	*rgb = vals;
	*linep = line;
	return (true);
}
x