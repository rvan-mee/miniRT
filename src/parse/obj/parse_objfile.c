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

static bool	is_valid_type(t_obj_type type)
{
	return (type == FACE ||
			type == COMMENT ||
			type == VERTEX ||
			type == VT_NORMAL ||
			type == VT_TEXTURE ||
			type == MTL ||
			type == USEMTL ||
			type == MTLLIB ||
			type == OBJ_GROUP ||
			type == OBJ_OBJ ||
			type == OBJ_SMOOTH);
}

static t_parse_err	parse_more(t_meshdat *dat)
{
	char		*line;
	t_object	obj;
	t_parse_err	err;

	err = get_line(&dat->conf, &line);
	if (err != CONTINUE)
		return (err);
	if (*line == '\n' || *line == '\0')
		return (free(line), CONTINUE);
	obj = (t_object){};
	if (!parse_object(line, &obj, &dat->conf))
		return (free(line), OBJECT);
	free(line);
	if (!is_valid_type(obj.type))
		return (INV_OBJ);
	if (obj.type == FACE && !dynarr_addone(&dat->conf.objects, &obj))
		return (DYNARR);
	return (CONTINUE);
}

t_parse_err	parse_objfile(char **linep, t_object *object, t_conf_data *conf)
{
	t_parse_err	err;
	t_meshdat	dat;
	char		*path;

	(void) object;
	err = parse_path(linep, &path);
	if (err != SUCCESS)
		return (err);
	err = init_meshdata(path, &dat);
	free(path);
	if (err != SUCCESS)
		return (err);
	dat.conf.has_mtl = conf->has_mtl;
	if (conf->has_mtl)
		dat.conf.curr_mtl = -1;
	err = CONTINUE;
	while (err == CONTINUE)
		err = parse_more(&dat);
	if (err == SUCCESS)
		return (create_mesh(&dat, conf));
	destroy_meshdata(&dat, true, true);
	return (err);
}
