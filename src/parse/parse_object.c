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
#include <sort.h>

#define ID_COUNT	21

static t_parse_err	(*g_parsefun[])(char **, t_object *, t_conf_data *) = {\
	[AMBIENT] = parse_ambient,		\
	[CAMERA] = parse_camera,		\
	[LIGHT] = parse_light,			\
	[SPHERE] = parse_sphere,		\
	[PLANE] = parse_plane,			\
	[CYLINDER] = parse_cylinder,	\
	[TRIANGLE] = parse_triangle,	\
	[VERTEX] = parse_obj_vec,		\
	[VT_TEXTURE] = parse_obj_vec,	\
	[VT_NORMAL] = parse_obj_vec,	\
	[FACE] = parse_face,			\
	[MTL] = parse_newmtl,			\
	[USEMTL] = parse_usemtl,		\
	[EXPOSURE] = parse_exposure,	\
	[OBJFILE] = parse_objfile,		\
	[USEMESH] = parse_usemesh,		\
	[MTLLIB] = parse_mtlfile,		\
	[OBJ_SMOOTH] = parse_smoothing,	\
};

static const char	*g_ids[] = {\
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
	[USEMESH] = "usemesh",			\
	[MTLLIB] = "mtllib",			\
	[OBJ_GROUP] = "g",				\
	[OBJ_SMOOTH] = "s",				\
	[OBJ_OBJ] = "o",				\
};

static int32_t	compare_ids(const t_obj_type *a, const t_obj_type *b, void *ign)
{
	(void) ign;
	return (ft_strncmp(g_ids[*b], g_ids[*a], SIZE_MAX));
}

static void	init_search_data(t_obj_type sorted[], size_t lens[])
{
	t_obj_type	t;
	size_t		i;
	t_sort		sort;

	i = 0;
	t = 0;
	while (i < ID_COUNT)
	{
		if (g_ids[t])
			sorted[i++] = t;
		++t;
	}
	sort = (t_sort){\
		sorted, sizeof(t_obj_type), (t_cmp) compare_ids, NULL
	};
	sinssort(&sort, 0, ID_COUNT);
	i = ID_COUNT;
	while (i--)
		lens[i] = ft_strlen(g_ids[sorted[i]]);
}

static
size_t	bsearch_type(char *line, const t_obj_type sorted[], const size_t lens[])
{
	size_t	l;
	size_t	r;
	size_t	idx;
	int32_t	cmp;

	l = 0;
	r = ID_COUNT - 1;
	while (l < r)
	{
		idx = (l + r) / 2;
		cmp = ft_strncmp(g_ids[sorted[idx]], line, lens[idx]);
		if (cmp > 0)
			l = idx + 1;
		else
			r = idx;
	}
	if (ft_strncmp(g_ids[sorted[l]], line, lens[l]))
		return (SIZE_MAX);
	return (l);
}

static t_obj_type	get_obj_type(char *line, size_t *id_len)
{
	static t_obj_type	sorted[ID_COUNT] = {-1};
	static size_t		lens[ID_COUNT];
	t_obj_type			type;
	size_t				index;

	if (sorted[0] == (t_obj_type) -1)
		init_search_data(sorted, lens);
	index = bsearch_type(line, sorted, lens);
	if (index == SIZE_MAX)
		return (END);
	*id_len = lens[index];
	type = sorted[index];
	return (type);
}

bool	parse_object(char *line, t_object *object, t_conf_data *conf)
{
	const char	*start_line = line;
	t_parse_err	err;
	size_t		id_len;

	id_len = 0;
	object->type = get_obj_type(line, &id_len);
	object->has_mat = conf->has_mtl;
	object->mat_idx = conf->curr_mtl;
	if (is_ignored_type(object->type))
		return (true);
	line += id_len;
	if (object->type == END || !ft_isspace(*line))
		return (parse_line_error(start_line, OBJECT, conf->curr_line));
	skip_spaces(&line);
	err = g_parsefun[object->type](&line, object, conf);
	if (err != SUCCESS)
		return (parse_line_error(start_line, err, conf->curr_line));
	skip_spaces(&line);
	if (*line != '\0')
		return (parse_line_error(start_line, FORMAT, conf->curr_line));
	return (true);
}
