/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 19:20:49 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 16:35:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static t_parse_error	(*g_parsefun[])(char **, t_object *, t_conf_data *) = {\
	[AMBIENT] = parse_ambient,									\
	[CAMERA] = parse_camera,									\
	[LIGHT] = parse_light,										\
	[SPHERE] = parse_sphere,									\
	[PLANE] = parse_plane,										\
	[CYLINDER] = parse_cylinder,								\
	[TRIANGLE] = parse_triangle,								\
	[VERTEX] = parse_obj_vec,									\
	[VT_TEXTURE] = parse_obj_vec,								\
	[VT_NORMAL] = parse_obj_vec,								\
	[FACE] = parse_face,										\
	[MTL] = parse_newmtl,										\
	[USEMTL] = parse_usemtl,									\
	[EXPOSURE] = parse_exposure,								\
	[OBJFILE] = parse_objfile,									\
	[USEMESH] = parse_usemesh,									\
};

static const char		*g_ids[] = {\
	[AMBIENT] = "A",				\
	[CAMERA] = "C",					\
	[LIGHT] = "L",					\
	[SPHERE] = "sp",				\
	[PLANE] = "pl",					\
	[CYLINDER] = "cy",				\
	[TRIANGLE] = "tri",				\
	[VT_TEXTURE] = "vt",			\
	[VT_NORMAL] = "vn",				\
	[VERTEX] = "v",					\
	[FACE] = "f",					\
	[COMMENT] = "#",				\
	[MTL] = "newmtl",				\
	[USEMTL] = "usemtl",			\
	[EXPOSURE] = "exposure",		\
	[OBJFILE] = "objfile",			\
	[USEMESH] = "usemesh"			\
};

static t_obj_type	get_obj_type(char *line, t_object *object, size_t *id_len)
{
	t_obj_type		type;

	type = UNINITIALIZED;
	while (++type != END)
	{
		*id_len = ft_strlen(g_ids[type]);
		if (ft_strncmp(g_ids[type], line, *id_len) == 0)
		{
			if (type == COMMENT)
			{
				object->type = COMMENT;
				return (COMMENT);
			}
			break ;
		}
	}
	return (type);
}

bool	parse_object(char *line, t_object *object, t_conf_data *conf)
{
	const char		*start_line = line;
	t_obj_type		type;
	t_parse_error	err;
	size_t			id_len;

	type = get_obj_type(line, object, &id_len);
	if (type == COMMENT)
		return (true);
	line += id_len;
	if (type == END || !ft_isspace(*line))
		return (parse_line_error(start_line, OBJECT, conf->curr_line));
	object->type = type;
	object->has_mat = conf->has_mtl;
	object->mat_idx = conf->curr_mtl;
	skip_spaces(&line);
	err = g_parsefun[type](&line, object, conf);
	if (err != SUCCESS)
		return (parse_line_error(start_line, err, conf->curr_line));
	skip_spaces(&line);
	if (*line != '\0')
		return (parse_line_error(start_line, FORMAT, conf->curr_line));
	return (true);
}
