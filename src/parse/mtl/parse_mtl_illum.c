/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl_illum.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:51:05 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 16:47:33 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static bool	parse_num(char **linep, int32_t *num)
{
	char	*line;
	size_t	i;

	line = *linep;
	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (i == 0)
		return (false);
	*num = ft_atoi(line);
	if (*num > 10 || *num < 0)
		return (false);
	*linep = &line[i];
	return (true);
}

t_parse_err	parse_mtl_illum(char *line, t_object *object)
{
	int32_t	illum;

	if (is_flag(&object->material, ILLUM_MODE))
		return (DUPLICATE);
	skip_spaces(&line);
	if (!parse_num(&line, &illum))
		return (ILLUM);
	skip_spaces(&line);
	if (*line)
		return (ILLUM);
	set_flag(&object->material, ILLUM_MODE);
	object->material.illum = illum;
	return (CONTINUE);
}
