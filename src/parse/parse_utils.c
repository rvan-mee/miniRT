/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 11:28:47 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/12 21:26:15 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

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
#define INDEX_ERROR		"does not contain a valid index\n"
#define VERT_ERROR		"does not contain a valid vertex\n"
#define V_TX_ERROR		"does not contain a valid vertex texture\n"
#define VN_ERROR		"does not contain a valid vertex normal\n"
#define MATCH_ERROR		"does not have the same elements across all parameters\n"
#define MTL_ERROR		"does not contain valid material properties\n"
#define NAME_ERROR		"does not contain valid material name\n"
#define DUP_ERROR		"has a duplicate material name\n"
#define ALLOC_ERROR		"failed to allocate memory\n"
#define KA_ERROR		"\nthis material contains an invalid ambient colour\n"
#define KD_ERROR		"\nthis material contains an invalid diffuse colour\n"
#define KS_ERROR		"\nthis material contains an invalid specular colour\n"
#define KE_ERROR		"\nthis material contains an invalid emissive colour\n"
#define ILLUM_ERROR		"\nthis material contains an invalid illumination value\n"
#define NS_ERROR		"\nthis material contains an invalid specular value\n"
#define D_ERROR			"\nthis material contains an invalid dissolve value\n"
#define TR_ERROR		"\nthis material contains an invalid transparency value\n"
#define NI_ERROR		"\nthis material contains an invalid optical density value\n"
#define TF_ERROR		"\nthis material contains an invalid transmission filter colour\n"
#define DUPLICATE_ERROR	"\nthis material contains duplicate elements\n"
#define DYNARR_ERROR	"failed to add to the dynamic array\n"
#define ERR_EXTENSION	"Error\nWrong file extension: `%s'\n"
#define ERR_OPEN		"Error\nFile failed to open: %s: %s\n"

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
	[OBJ_HEIGHT] = HEIGHT_ERROR,
	[INDEX] = INDEX_ERROR,
	[VERT] = VERT_ERROR,
	[VERT_TEXTURE] = V_TX_ERROR,
	[NORMAL] = VN_ERROR,
	[DYNARR] = DYNARR_ERROR,
	[MATCH] = MATCH_ERROR,
	[MTL_ERR] = MTL_ERROR,
	[NAME] = NAME_ERROR,
	[DUP] = DUP_ERROR,
	[ALLOC] = ALLOC_ERROR,
	[KA] = KA_ERROR,
	[KD] = KD_ERROR,
	[KS] = KS_ERROR,
	[KE] = KE_ERROR,
	[ILLUM] = ILLUM_ERROR,
	[NS] = NS_ERROR,
	[D] = D_ERROR,
	[TR] = TF_ERROR,
	[NI] = NI_ERROR,
	[TF] = TF_ERROR,
	[DUPLICATE] = DUPLICATE_ERROR,
	};
	char		*newline;

	newline = ft_strchr(line, '\n');
	if (newline != NULL)
		*newline = '\0';
	dprintf(STDERR_FILENO, PARSE_ERROR, line, message[err]);
	return (false);
}

bool	check_extension(const char *path, char *ext)
{
	const size_t	len_path = ft_strlen(path);
	const size_t	len_ext = ft_strlen(ext);

	if (ft_strncmp(&path[len_path - len_ext], ext, len_ext) == 0)
		return (true);
	dprintf(STDERR_FILENO, ERR_EXTENSION, path);
	return (false);
}

bool	open_file(const char *path, int32_t *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd != -1)
		return (true);
	dprintf(STDERR_FILENO, ERR_OPEN, path, strerror(errno));
	return (false);
}

void	skip_spaces(char **linep)
{
	const char	*line = *linep;

	while (ft_isspace(*line))
		line++;
	*linep = (char *) line;
}

void	skip_digits(char **linep)
{
	const char	*line = *linep;

	while (ft_isdigit(*line))
		line++;
	*linep = (char *) line;
}
