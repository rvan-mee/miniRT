/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtlfile.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 23:35:35 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/21 23:35:35 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <get_next_line.h>
#include <unistd.h>

static t_parse_err	parse_path(char **linep, char **dst)
{
	char	*line;

	line = *linep;
	while (*line && !ft_isspace(*line))
		++line;
	*dst = ft_substr(*linep, 0, line - *linep);
	*linep = line;
	if (!*dst)
		return (ALLOC);
	return (SUCCESS);
}

static t_parse_err	init_data(char *path, t_conf_data *conf)
{
	if (!check_extension(path, ".mtl"))
		return (MTL_EXT);
	else if (!open_file(path, &conf->fd))
		return (MTL_NF);
	conf->curr_line = 0;
	return (SUCCESS);
}

static t_parse_err	parse_more(t_conf_data *conf)
{
	char		*line;
	t_object	obj;

	line = get_next_line(conf->fd);
	if (line == NULL)
		return (SUCCESS);
	if (*line == '\n' || *line == '\0')
		return (free(line), CONTINUE);
	obj = (t_object){};
	if (!parse_object(line, &obj, conf))
		return (free(line), OBJECT);
	free(line);
	if (obj.type != COMMENT && obj.type != MTL)
		return (INV_MTL);
	return (CONTINUE);
}

t_parse_err	parse_mtlfile(char **linep, t_object *object, t_conf_data *conf)
{
	const int32_t	old_fd = conf->fd;
	const size_t	old_lineno = conf->curr_line;
	t_parse_err		err;
	char			*path;

	(void) object;
	err = parse_path(linep, &path);
	if (err != SUCCESS)
		return (err);
	err = init_data(path, conf);
	free(path);
	if (err != SUCCESS)
		return (err);
	err = CONTINUE;
	while (err == CONTINUE)
		err = parse_more(conf);
	close(conf->fd);
	conf->curr_line = old_lineno;
	conf->fd = old_fd;
	return (err);
}
