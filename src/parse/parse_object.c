/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 19:20:49 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/04 19:10:09 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static t_parse_error	(*g_parsefun[])(char **, t_object *) = {\
	[AMBIENT] = parse_ambient,									\
	[CAMERA] = parse_camera,									\
	[LIGHT] = parse_light,										\
	[SPHERE] = parse_sphere,									\
	[PLANE] = parse_plane,										\
	[CYLINDER] = parse_cylinder,								\
	[TRIANGLE] = parse_triangle,								\
};

static const char		*g_ids[] = {\
	[AMBIENT] = "A",				\
	[CAMERA] = "C",					\
	[LIGHT] = "L",					\
	[SPHERE] = "sp",				\
	[PLANE] = "pl",					\
	[CYLINDER] = "cy",				\
	[TRIANGLE] = "tr",				\
};

bool	parse_object(char *line, t_object *object)
{
	const char		*start_line = line;
	t_obj_type		type;
	t_parse_error	err;
	size_t			id_len;

	type = UNINITIALIZED;
	while (++type != END)
	{
		id_len = ft_strlen(g_ids[type]);
		if (ft_strncmp(g_ids[type], line, id_len) == 0)
			break ;
	}
	line += id_len;
	if (type == END || !ft_isspace(*line))
		return (parse_line_error(start_line, OBJECT));
	object->type = type;
	skip_spaces(&line);
	err = g_parsefun[type](&line, object);
	if (err != SUCCESS)
		return (parse_line_error(start_line, err));
	skip_spaces(&line);
	if (*line != '\0')
		return (parse_line_error(start_line, FORMAT));
	return (true);
}
