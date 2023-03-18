/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_mesh.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:15:32 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/18 22:15:32 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parse_obj.h>
#include <ft_math.h>

static bool	find_mesh(char *name, t_conf_data *conf, const t_mesh **dst)
{
	const t_mesh	*meshes = conf->meshes.arr;
	const size_t	n = conf->meshes.length;
	const size_t	name_len = ft_strlen(name);
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (ft_strncmp(name, meshes[i].name, name_len + 1) == 0)
		{
			*dst = meshes + i;
			free(name);
			return (true);
		}
		++i;
	}
	free(name);
	return (false);
}

static void	to_world(t_fvec *vec, t_meshparams params, bool norm)
{
	t_fvec	tmp;

	tmp = *vec;
	if (!norm)
		tmp *= params.scale;
	*vec = tmp[X] * params.u + tmp[Y] * params.v + tmp[Z] * params.w;
	if (norm)
		*vec = normalize_vector(*vec);
	else
		*vec += params.coords;
}

static
bool	add_faces(const t_mesh *mesh, t_meshparams params, t_conf_data *conf)
{
	t_object	*obj;
	size_t		i;

	i = conf->objects.length;
	if (!dynarr_add(&conf->objects, mesh->faces, mesh->length))
		return (false);
	while (i < conf->objects.length)
	{
		obj = dynarr_get(&conf->objects, i++);
		to_world(&obj->coords, params, false);
		to_world(&obj->face.vert[0], params, false);
		to_world(&obj->face.vert[1], params, false);
		to_world(&obj->face.vert[2], params, false);
		if (obj->face.has_normal)
		{
			to_world(&obj->face.normals[0], params, true);
			to_world(&obj->face.normals[1], params, true);
			to_world(&obj->face.normals[2], params, true);
		}
		obj->face.v0v1 = obj->face.vert[1] - obj->face.vert[0];
		obj->face.v0v2 = obj->face.vert[2] - obj->face.vert[0];
	}
	return (true);
}

t_parse_error	add_mesh(t_meshparams params, t_conf_data *conf)
{
	const t_mesh	*mesh;

	if (!find_mesh(params.name, conf, &mesh))
		return (NAME);
	if (!add_faces(mesh, params, conf))
		return (DYNARR);
	return (SUCCESS);
}
