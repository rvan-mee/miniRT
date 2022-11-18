/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_map.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 17:45:40 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 20:08:17 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <parse_mtl.h>
#include <minirt.h>
#include <bmp.h>
#include <libft.h>

t_parse_error	parse_mtl_map(char *line, t_bmp *bmp)
{
	char	*path;
	size_t	i;

	i = 0;
	skip_spaces(&line);
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	if (i < 4)
		return (EXTENTION);
	printf("line: -%s-", line);
	path = ft_substr(line, 0, i);
	if (!path)
		return (ALLOC);
	printf("%d\n", *(line + i + 4));
	if (*(line + i + 4))
		return (free(path), EXTENTION);
	if (!check_extension(line, ".bmp"))
		return (free(path), EXTENTION);
	if (!parse_bmp(path, bmp))
		return (free(path), BMP_ERR);
	return (SUCCESS);
}
