/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 11:28:47 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/14 17:21:28 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <miniRT.h>
#include <libft.h>
#include <unistd.h>

#define WHITESPACE	"\t\n\v\f\r "

#define LINE_ERROR		"Error\nLine `"
#define OBJECT_ERROR	"' does not contain a valid object\n"
#define COORD_ERROR		"' does not contain valid coordinates\n"
#define VECTOR_ERROR	"' does not contain a valid orientation vector\n"
#define COLOUR_ERROR	"' does not contain a valid colour\n"
#define FORMAT_ERROR	"' does not contain a valid format\n"
#define LRATIO_ERROR	"' does not contain a valid lighting ratio\n"
#define FOV_ERROR		"' does not contain a valid fov\n"
#define BRIGHT_ERROR	"' does not contain a valid brightness\n"
#define DIA_ERROR		"' does not contain a valid diameter\n"
#define HEIGHT_ERROR	"' does not contain a valid height\n"

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

bool	parse_line_error(const char *line, t_parse_error err)
{
	const char	*message[] = {
	[OBJECT] = OBJECT_ERROR,
	[COORD] = COORD_ERROR,
	[VECTOR] = VECTOR_ERROR,
	[COLOUR] = COLOUR_ERROR,
	[FORMAT] = FORMAT_ERROR,
	[LRATIO] = LRATIO_ERROR,
	[FOV] = FOV_ERROR,
	[BRIGHT] = BRIGHT_ERROR,
	[DIAMETER] = DIA_ERROR,
	[OBJ_HEIGHT] = HEIGHT_ERROR
	};

	ft_putstr_fd(LINE_ERROR, STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd(message[err], STDERR_FILENO);
	return (false);
}

bool	is_space(char c)
{
	if (c != '\0' && ft_strchr(WHITESPACE, c) != NULL)
		return (true);
	return (false);
}

void	skip_spaces(char **linep)
{
	const char	*line = *linep;

	while (is_space(*line))
		line++;
	*linep = (char *) line;
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
