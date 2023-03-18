/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_objfile.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:18:40 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/18 22:18:40 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse_obj.h>
#include <stdlib.h>
#include <libft.h>
#include <get_next_line.h>

static t_parse_error	parse_path(char **linep, char **dst)
{
	char	*line;

	skip_spaces(linep);
	line = *linep;
	while (*line && !ft_isspace(*line))
		++line;
	*dst = ft_substr(*linep, 0, line - *linep);
	*linep = line;
	if (!*dst)
		return (ALLOC);
	return (SUCCESS);
}

static t_parse_error	parse_more(t_meshdat *dat)
{
	char		*line;
	t_object	obj;

	line = get_next_line(dat->conf.fd);
	if (line == NULL)
		return (SUCCESS);
	if (*line == '\n' || *line == '\0')
		return (free(line), CONTINUE);
	obj = (t_object){};
	if (!parse_object(line, &obj, &dat->conf))
		return (free(line), OBJECT);
	free(line);
	if (obj.type == COMMENT || obj.type == VERTEX || obj.type == VT_NORMAL || \
		obj.type == VT_TEXTURE || obj.type == MTL || obj.type == USEMTL)
		return (CONTINUE);
	if (obj.type != FACE)
		return (INV_OBJ);
	if (!dynarr_addone(&dat->conf.objects, &obj))
		return (DYNARR);
	return (CONTINUE);
}

t_parse_error	parse_objfile(char **linep, t_object *object, t_conf_data *conf)
{
	t_parse_error	err;
	t_meshdat		dat;
	char			*path;

	(void) object;
	err = parse_path(linep, &path);
	if (err != SUCCESS)
		return (err);
	if (!init_meshdata(path, &dat))
		return (free(path), DYNARR); // todo: error msg
	free(path);
	dat.conf.has_mtl = conf->has_mtl;
	if (conf->has_mtl)
		dat.conf.curr_mtl = -1;
	err = CONTINUE;
	while (err == CONTINUE)
		err = parse_more(&dat);
	if (err != SUCCESS)
		return (destroy_meshdata(&dat, true, true), err);
	if (!create_mesh(&dat, conf))
		return (DYNARR);
	return (SUCCESS);
}
