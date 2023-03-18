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

typedef struct s_face_indices {
	int32_t	vert_index;
	bool	has_texture;
	bool	has_normal;
	int32_t	normal_index;
	int32_t	vert_texture_index;
}	t_face_indices;

static bool	parse_normal(char **linep, t_face_indices *index, t_conf_data *conf)
{
	char	*line;
	int32_t	new_index;

	line = *linep;
	if (*line != '/')
		return (false);
	line++;
	if (!ft_isdigit(*line) && *line != '-')
		return (false);
	index->has_normal = true;
	new_index = ft_atoi(line) - 1;
	if (new_index < 0)
		new_index += conf->v.length + 1;
	if (new_index < 0 || (size_t)new_index > conf->vn.length)
		return (false);
	line++;
	skip_digits(&line);
	index->normal_index = new_index;
	*linep = line;
	return (true);
}

static bool	parse_vertex_texture(char **linep, \
								t_face_indices *index, t_conf_data *conf)
{
	char	*line;
	int32_t	new_index;

	line = *linep;
	if (!ft_isdigit(*line) && *line != '-')
		return (false);
	new_index = ft_atoi(line) - 1;
	if (new_index < 0)
		new_index += conf->v.length + 1;
	if (new_index < 0 || (size_t)new_index > conf->vt.length)
		return (false);
	index->vert_texture_index = new_index;
	line++;
	skip_digits(&line);
	if (*line == '/')
		index->has_normal = true;
	*linep = line;
	return (true);
}

static bool	parse_vert_index(char **linep, \
							t_face_indices *index, t_conf_data *conf)
{
	char	*line;
	int32_t	new_index;

	line = *linep;
	skip_spaces(&line);
	if (!ft_isdigit(*line) && *line != '-')
		return (false);
	new_index = ft_atoi(line) - 1;
	if (new_index < 0)
		new_index += conf->v.length + 1;
	if (new_index < 0 || (size_t)new_index > conf->v.length)
		return (false);
	index->vert_index = new_index;
	line++;
	skip_digits(&line);
	if (*line == '/')
	{
		line++;
		if (ft_isdigit(*line) || *line == '-')
			index->has_texture = true;
		else if (*line == '/')
			index->has_normal = true;
		else
			return (false);
	}
	*linep = line;
	return (true);
}

static t_parse_error	parse_indices(
	char **linep, \
	t_face_indices *index, \
	t_conf_data *conf, \
	int32_t check_pre)
{
	const bool	pre_has_texture = index->has_texture;
	const bool	pre_has_normal = index->has_normal;
	char		*line;

	line = *linep;
	index->has_texture = false;
	index->has_normal = false;
	if (!parse_vert_index(&line, index, conf))
		return (INDEX);
	if (check_pre && index->has_texture != pre_has_texture)
		return (MATCH);
	if (index->has_texture && !parse_vertex_texture(&line, index, conf))
		return (VERT_TEXTURE);
	if (check_pre && index->has_normal != pre_has_normal)
		return (MATCH);
	if (index->has_normal && !parse_normal(&line, index, conf))
		return (NORMAL);
	*linep = line;
	return (SUCCESS);
}

static void	set_indices(
	t_object *object, \
	t_conf_data *conf, \
	t_face_indices *index, \
	int32_t vert)
{
	const t_fvec	*normals = conf->vn.arr;
	const t_fvec	*vertices = conf->v.arr;
	const t_fvec	*texture = conf->vt.arr;

	object->face.vert[vert] = vertices[index->vert_index];
	if (index->has_normal)
		object->face.normals[vert] = normals[index->normal_index];
	if (index->has_texture)
		object->face.uvw[vert] = texture[index->vert_texture_index];
}
#include <math.h>
t_parse_error	parse_face(char **linep, t_object *object, t_conf_data *conf)
{
	t_face_indices	indices;
	t_parse_error	err;
	char			*line;
	int32_t			vert;

	line = *linep;
	vert = A;
	indices.has_normal = false;
	indices.has_texture = false;
	object->colour = (t_fvec){1, 1, 1};
	while (vert <= C)
	{
		err = parse_indices(&line, &indices, conf, vert);
		if (err != SUCCESS)
			return (err);
		set_indices(object, conf, &indices, vert);
		vert++;
	}
	object->face.has_normal = indices.has_normal;
	object->face.has_texture = indices.has_texture;
	object->face.v0v1 = object->face.vert[B] - object->face.vert[A];
	object->face.v0v2 = object->face.vert[C] - object->face.vert[A];
	object->coords[0] = (fminf(fminf(object->face.vert[0][X], object->face.vert[1][X]), object->face.vert[2][X]) + fmaxf(fmaxf(object->face.vert[0][X], object->face.vert[1][X]), object->face.vert[2][X])) / 2;
	object->coords[1] = (fminf(fminf(object->face.vert[0][Y], object->face.vert[1][Y]), object->face.vert[2][Y]) + fmaxf(fmaxf(object->face.vert[0][Y], object->face.vert[1][Y]), object->face.vert[2][Y])) / 2;
	object->coords[2] = (fminf(fminf(object->face.vert[0][Z], object->face.vert[1][Z]), object->face.vert[2][Z]) + fmaxf(fmaxf(object->face.vert[0][Z], object->face.vert[1][Z]), object->face.vert[2][Z])) / 2;
	*linep = line;
	return (SUCCESS);
}
