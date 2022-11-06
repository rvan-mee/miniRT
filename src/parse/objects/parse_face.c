/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_face.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 15:44:05 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/06 19:52:47 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parse.h>

#define	A 0
#define	B 1
#define	C 2

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
	if (!ft_isdigit(*line))
		return (false);
	index->has_normal = true;
	new_index = ft_atoi(line) - 1;
	if (new_index < 0 || (size_t)new_index > conf->vertex_normals.length)
		return (false);
	skip_digits(&line);
	index->normal_index = new_index;
	*linep = line;
	return(true);
}

static bool	parse_vertex_texture(char **linep, t_face_indices *index, t_conf_data *conf)
{
	char	*line;
	int32_t	new_index;

	line = *linep;
	new_index = ft_atoi(line) - 1;
	if (new_index < 0 || (size_t)new_index > conf->vertex_textures.length)
		return (false);
	index->vert_texture_index = new_index;
	skip_digits(&line);
	if (*line  == '/')
		index->has_normal = true;
	*linep = line;
	return (true);
}

static bool	parse_vert_index(char **linep, t_face_indices *index, t_conf_data *conf)
{
	char	*line;
	int32_t	new_index;

	line = *linep;
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (false);
	new_index = ft_atoi(line) - 1;
	if (new_index < 0 || (size_t)new_index > conf->vertices.length)
		return (false);
	index->vert_index = new_index;
	skip_digits(&line);
	if (*line == '/')
		line++;
	if (ft_isdigit(*line))
		index->has_texture = true;
	else if (*line == '/')
		index->has_normal = true;
	*linep = line;
	return (true);
}

static t_parse_error	parse_indices(char **linep, t_face_indices *index, t_conf_data *conf)
{
	char	*line;

	line = *linep;
	index->has_texture = false;
	index->has_normal = false;
	if (!parse_vert_index(&line, index, conf))
		return (INDEX);
	if (index->has_texture && !parse_vertex_texture(&line, index, conf))
		return (VERT_TEXTURE);
	if (index->has_normal && !parse_normal(&line, index, conf))
		return (NORMAL);
	*linep = line;
	return (SUCCESS);
}

static void	set_indices(t_object *object, t_conf_data *conf, t_face_indices *index, int32_t axis)
{
	const t_normals			*normals = conf->vertex_normals.arr;
	const t_vertex			*vertices = conf->vertices.arr;
	const t_vertex_texture	*texture = conf->vertex_textures.arr;

	object->face.vert[axis] = vertices[index->vert_index].point;
	if (index->has_normal)
		object->face.normals[axis] = normals[index->normal_index].normal;
	if (index->has_texture)
		object->face.uv[axis] = texture[index->normal_index].uv;
}

static void	pre_calc(t_face *face)
{
	face->v0v1 = face->vert[B] - face->vert[A];
	face->v0v2 = face->vert[C] - face->vert[A];
}

// TODO: fix that all indices have to contain the same variables (so no v1/vt1/vn1 and v2//vn2 in the same line)
t_parse_error	parse_face(char **linep, t_object *object, t_conf_data *conf)
{
	t_face_indices	indices;
	t_parse_error	err;			
	char			*line;
	int32_t			axis;

	line = *linep;
	axis = A;
	while (axis <= C)
	{
		err = parse_indices(&line, &indices, conf);
		if (err != SUCCESS)
			return (err);
		set_indices(object, conf, &indices, axis);
		axis++;
	}
	pre_calc(&object->face);
	printf("face contains: %f %f %f   %f %f %f  %f %f %f\n", object->face.vert[A][X], object->face.vert[A][Y], object->face.vert[A][Z], object->face.vert[B][X], object->face.vert[B][Y], object->face.vert[B][Z], object->face.vert[C][X], object->face.vert[C][Y], object->face.vert[C][Z]);
	*linep = line;
	return (SUCCESS);
}
