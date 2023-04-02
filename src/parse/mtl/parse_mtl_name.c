/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_name.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/11 23:41:12 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/03/11 23:41:12 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static bool	is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '-');
}

t_parse_err	parse_mtl_name(char **linep, char **name)
{
	size_t	name_len;
	char	*line;

	name_len = 0;
	line = *linep;
	while (is_valid_char(line[name_len]))
		name_len++;
	if (name_len == 0)
		return (NAME);
	*name = ft_substr(line, 0, name_len);
	if (!*name)
		return (ALLOC);
	line += name_len;
	skip_spaces(&line);
	if (*line)
	{
		free(*name);
		return (NAME);
	}
	*linep = line;
	return (SUCCESS);
}
