/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_usemtl.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 11:14:13 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/19 12:17:42 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <minirt.h>
#include <libft.h>

static t_parse_error	parse_mtl_name(char **linep, char **name)
{
	size_t		name_len;
	char 		*line;

	name_len = 0;
	line = *linep;
	skip_spaces(&line);
	if (!(ft_isalnum(*line)) && *line != '_' && *line != '-')
		return (NAME);
	while (ft_isalnum(line[name_len]) || line[name_len] == '_' \
			|| line[name_len] == '-')
		name_len++;
	*name = ft_substr(line, 0, name_len);
	if (!*name)
		return (ALLOC);
	line += name_len;
	skip_spaces(&line);
	if (*line)
		return (free(*name), NAME);
	*linep = line;
	return (SUCCESS);
}

static t_parse_error	set_current_mtl(char *name, t_conf_data *conf)
{
	const size_t	name_len = ft_strlen(name);
	t_mtl			*mtl_arr;
	size_t			i;

	i = 0;
	mtl_arr = conf->materials.arr;
	while (i < conf->materials.length)
	{
		if (ft_strncmp(name, mtl_arr[i].name, name_len + 1) == 0)
		{
			conf->has_mtl = true;
			conf->curr_mtl = &mtl_arr[i];
			return (free(name), SUCCESS);
		}
		i++;
	}
	conf->has_mtl = false;
	return (NON_EXIST);
}

t_parse_error	parse_usemtl(char **linep, t_object *object, t_conf_data *conf)
{
	t_parse_error	err;
	char			*name;

	(void) object;
	err = parse_mtl_name(linep, &name);
	if (err != SUCCESS)
		return (err);
	return (set_current_mtl(name, conf));
}
