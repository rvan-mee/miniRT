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
#include <libft.h>
#include <unistd.h>
#include <stdio.h>

#define PARSE_ERROR		"Error\nLine `%s' %s"
#define OBJECT_ERROR	"does not contain a valid object\n"
#define COORD_ERROR		"does not contain valid coordinates\n"
#define VECTOR_ERROR	"does not contain a valid orientation vector\n"
#define COLOUR_ERROR	"does not contain a valid colour\n"
#define FORMAT_ERROR	"does not contain a valid format\n"
#define LRATIO_ERROR	"does not contain a valid lighting ratio\n"
#define FOV_ERROR		"does not contain a valid fov\n"
#define BRIGHT_ERROR	"does not contain a valid brightness\n"
#define DIA_ERROR		"does not contain a valid diameter\n"
#define HEIGHT_ERROR	"does not contain a valid height\n"

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
	char		*newline;

	newline = ft_strchr(line, '\n');
	if (newline != NULL)
		*newline = '\0';
	dprintf(STDERR_FILENO, PARSE_ERROR, line, message[err]);
	return (false);
}

void	skip_spaces(char **linep)
{
	const char	*line = *linep;

	while (ft_isspace(*line))
		line++;
	*linep = (char *) line;
}
