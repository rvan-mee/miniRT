/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 11:28:47 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/13 14:53:17 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <miniRT.h>
#include <libft.h>
#include <unistd.h>

#define LINE_ERROR		"Error\nLine `"
#define OBJECT_ERROR	"' does not contain a valid object\n"
#define COORD_ERROR		"' does not contain valid coordinates\n"
#define VECTOR_ERROR	"' does not contain a valid orientation vector\n"
#define COLOUR_ERROR	"' does not contain a valid colour\n"
#define FORMAT_ERROR	"' does not contain a valid format\n"
#define LRATIO_ERROR	"' does not contain a valid lightning ratio\n"

static bool	parse_color(char *line, char **end, uint8_t *colour)
{
	size_t	i;
	int32_t	num;
	char	str[4];

	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (i > 3 || i == 0 || line[i] == '\0')
		return (false);
	ft_strlcpy(str, line, i + 1);
	num = ft_atoi(str);
	if (num > 255 || num < 0)
		return (false);
	*colour = num;
	*end = &line[i];
	return (true);
}

bool	parse_line_error(char *line, t_parse_error err)
{
	const char	*message[] = {OBJECT_ERROR, COORD_ERROR, VECTOR_ERROR, \
							COLOUR_ERROR, FORMAT_ERROR, LRATIO_ERROR};

	write(STDERR_FILENO, LINE_ERROR, 13);
	write(STDERR_FILENO, line, ft_strlen(line));
	write(STDERR_FILENO, message[err], ft_strlen(message[err]));
	return (false);
}

bool	parse_vector(char *line, t_fvec *vector, bool normalized)
{
	return (true);
}

bool	parse_rgb(char *line, t_rgba *colour)
{
	while (*line && *line == ' ')
		line++;
	colour->a = 255;
	if (!parse_color(line, &line, &colour->r) || *line != ',')
		return (false);
	line++;
	if (!parse_color(line, &line, &colour->g) || *line != ',')
		return (false);
	line++;
	if (!parse_color(line, &line, &colour->b) || *line != '\n')
		return (false);
	return (true);
}
