/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_map.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 17:45:40 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/25 20:53:36 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_err	parse_mtl_map(char *line, t_bmp *bmp)
{
	char	*path;
	size_t	i;

	i = 0;
	skip_spaces(&line);
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (i < 4)
		return (TEX_EXT);
	path = ft_substr(line, 0, i);
	if (!path)
		return (ALLOC);
	if (!check_extension(path, ".bmp"))
		return (free(path), TEX_EXT);
	if (!parse_bmp(path, bmp))
		return (free(path), BMP_ERR);
	free(path);
	return (SUCCESS);
}
