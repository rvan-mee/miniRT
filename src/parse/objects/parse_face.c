/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_face.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 15:44:05 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/25 20:48:11 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parse.h>

#define A 0
#define B 1
#define C 2

static void	precalc(t_object *obj)
{
	const t_aabb	bounds = calc_bounds(obj);
	t_face			*face;

	face = &obj->face;
	face->v0v1 = face->vert[B] - face->vert[A];
	face->v0v2 = face->vert[C] - face->vert[A];
	obj->coords = (bounds.min + bounds.max) / 2.f;
}

static void	skip_int(char **linep)
{
	char	*line;

	line = *linep;
	if (*line == '-' || *line == '+')
		++line;
	while (ft_isdigit(*line))
		++line;
	*linep = line;
}

static const t_parse_err	g_errs[] = {VERT, VERT_TEXTURE, NORMAL};

static t_parse_err	parse_is(char **linep, int32_t dst[3], const size_t len[3])
{
	uint8_t	i;

	skip_spaces(linep);
	i = 0;
	while (true)
	{
		dst[i] = ft_atoi(*linep);
		if (dst[i] < 0)
			dst[i] += (int32_t) len[i] + 1;
		if (dst[i] < 0 || dst[i] > (int32_t) len[i])
			return (g_errs[i]);
		skip_int(linep);
		if (**linep == '\0' || ft_isspace(**linep))
			break ;
		if ((i < 2 && **linep != '/') || i == 2)
			return (g_errs[i]);
		(*linep) += 1;
		++i;
	}
	return (SUCCESS);
}

static
t_parse_err	set_idxs(t_face *face, int32_t idxs[3][3], t_conf_data *conf)
{
	const t_fvec	*v = conf->v.arr;
	const t_fvec	*vt = conf->vt.arr;
	const t_fvec	*vn = conf->vn.arr;
	uint8_t			i;

	if (idxs[0][0] == 0 || idxs[1][0] == 0 || idxs[2][0] == 0)
		return (VERT);
	face->has_texture = (idxs[0][1] || idxs[1][1] || idxs[2][1]);
	if (face->has_texture && (!idxs[0][1] || !idxs[1][1] || !idxs[2][1]))
		return (VERT_TEXTURE);
	face->has_normal = conf->smoothing && (idxs[0][2] || idxs[1][2] || idxs[2][2]);
	if (face->has_normal && (!idxs[0][2] || !idxs[1][2] || !idxs[2][2]))
		return (NORMAL);
	i = 3;
	while (i--)
	{
		face->vert[i] = v[idxs[i][0] - 1];
		if (face->has_texture)
			face->uvw[i] = vt[idxs[i][1] - 1];
		if (face->has_normal)
			face->normals[i] = vn[idxs[i][2] - 1];
	}
	return (SUCCESS);
}

t_parse_err	parse_face(char **linep, t_object *object, t_conf_data *conf)
{
	const size_t	len[3] = {conf->v.length, conf->vt.length, conf->vn.length};
	int32_t			idxs[3][3];
	uint8_t			vert;
	t_parse_err		err;

	vert = A;
	ft_bzero(idxs, sizeof(idxs));
	object->colour = (t_fvec){1, 1, 1};
	while (vert <= C)
	{
		err = parse_is(linep, idxs[vert++], len);
		if (err != SUCCESS)
			return (err);
		if (vert <= C && (**linep == '\0' || **linep == '\n'))
			return (INDEX);
	}
	err = set_idxs(&object->face, idxs, conf);
	if (err == SUCCESS)
		precalc(object);
	return (err);
}
