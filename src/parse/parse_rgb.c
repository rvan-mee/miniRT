/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rgb.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 19:52:27 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/14 19:52:27 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static bool	parse_colour(char **linep, uint8_t *colour)
{
	char	*line;
	size_t	i;
	int32_t	num;

	line = *linep;
	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (i == 0)
		return (false);
	num = ft_atoi(line);
	if (num > 255)
		return (false);
	*colour = num;
	*linep = &line[i];
	return (true);
}

bool	parse_rgb(char **linep, t_rgba *colour)
{
	char	*line;

	line = *linep;
	colour->a = 255;
	skip_spaces(&line);
	if (!parse_colour(&line, &colour->r) || *line++ != ',')
		return (false);
	if (!parse_colour(&line, &colour->g) || *line++ != ',')
		return (false);
	if (!parse_colour(&line, &colour->b))
		return (false);
	*linep = line;
	return (true);
}
