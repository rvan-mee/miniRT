/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_face.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 15:44:05 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/04 18:04:25 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parse.h>

#define	X 0
#define	Y 1
#define	Z 2

typedef struct s_face_indices {
	int32_t	vert_index;
	bool	has_texture;
	bool	has_normal;
	int32_t	normal_index;
	int32_t	vert_texture_index;
}	t_face_indices;

static bool	parse_normal(char **linep, t_face_indices *index)
{
	char	*line;

	line = *linep;
	if (*line != '/')
		return (false);
	line++;
	if (!ft_isdigit(*line))
		return (false);
	index->has_normal = true;
	index->normal_index = ft_atoi(line);
	skip_digits(&line);
	*linep = line;
	return(true);
}

static bool	parse_vertex_texture(char **linep, t_face_indices *index)
{
	char	*line;

	line = *linep;
	if (*line != '/')
		return (false);
	line++;
	if (*line == '/')
	{
		*linep = line;
		return (true);
	}
	if (!ft_isdigit(*line))
		return (false);
	index->has_texture = true;
	index->vert_texture_index = ft_atoi(line);
	skip_digits(&line);
	*linep = line;
	return (true);
}

static bool	parse_vert_index(char **linep, t_face_indices *index)
{
	char	*line;

	line = *linep;
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (false);
	index->normal_index = ft_atoi(line);
	skip_digits(&line);
	*linep = line;
	return (true);
}

static bool	parse_indices(char **linep, t_face_indices *index)
{
	char	*line;

	line = *linep;
	index->has_texture = false;
	index->has_normal = false;
	if (!parse_vert_index(&line, index))
		return (INDEX);
	if (!parse_vertex_texture(&line, index))
		return (VERT_TEXTURE);
	if (!parse_normal(&line, index))
		return (NORMAL);
	*linep = line;
	return (SUCCESS);
}

bool	set_indices(t_object *object, t_conf_data *data, t_face_indices *index, int32_t axis)
{
	const t_normals	*normals = data->vertex_normals.arr;
	const t_vertex	*vertices = data->vertices.arr;
	const t_uv		*uv = data->uv.arr;

	if (index->vert_index > data->vertices.length)
		return (false);
	object->face.vert[axis] = vertices[index->vert_index];
	if (index->has_normal)
	{
		if (index->normal_index > data->vertex_normals.length)
			return (false);
		object->face.normals[axis] = normals[index->normal_index];
	}
	if (index->has_texture)
	{
		if (index->vert_texture_index > data->vertex_textures.length)
			return (false);
		object->face.uv[axis] = texture index->normal_index];
	}
	return (true);
}

t_object	parse_face(char **linep, t_object *object, t_conf_data *data)
{
	t_face_indices	indices;
	t_parse_error	err;			
	char			*line;

	line = *linep;
	err = parse_indices(&line, &indices);
	if (err != SUCCESS)
		return (err);
	if (!set_indices(object, data, &indices))
		return (INDICES);
	err = parse_indices(&line, &indices);
	if (err != SUCCESS)
		return (err);
	if (!set_indices(object, data, &indices))
		return (INDICES);
	err = parse_indices(&line, &indices);
	if (err != SUCCESS)
		return (err);
	if (!set_indices(object, data, &indices))
		return (INDICES);
	*linep = line;
	return (SUCCESS);
}
