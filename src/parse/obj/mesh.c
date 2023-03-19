/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mesh.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:16:28 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/18 22:16:28 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse_obj.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

static void	offset_mtl(t_object *object, void *delta)
{
	if (object->has_mat)
		object->mat_idx += (size_t) delta;
}

static bool	add_mtls(t_conf_data *meshdata, t_conf_data *conf)
{
	const size_t	idx = conf->materials.length;
	size_t			i;
	t_mtl			*mtl;

	i = 0;
	mtl = meshdata->materials.arr;
	while (i < meshdata->materials.length)
	{
		free(mtl[i].name);
		mtl[i].name = NULL;
		++i;
	}
	if (!dynarr_add(&conf->materials, mtl, meshdata->materials.length))
		return (false);
	dynarr_foreach(&meshdata->objects, (t_foreach) offset_mtl, (void *) idx);
	return (true);
}

static void	normalize_faces(t_mesh mesh, float scale, t_fvec offset)
{
	t_object	*face;
	size_t		i;

	i = 0;
	while (i < mesh.length)
	{
		face = mesh.faces + i++;
		face->coords = (face->coords + offset) * scale;
		face->face.vert[0] = (face->face.vert[0] + offset) * scale;
		face->face.vert[1] = (face->face.vert[1] + offset) * scale;
		face->face.vert[2] = (face->face.vert[2] + offset) * scale;
	}
}

static void	normalize_size(t_mesh mesh)
{
	t_aabb	bounds;
	t_fvec	size;
	float	sizef;
	size_t	i;

	bounds = (t_aabb){\
		{FLT_MAX, FLT_MAX, FLT_MAX}, {-FLT_MAX, -FLT_MAX, -FLT_MAX}
	};
	i = 0;
	while (i < mesh.length)
		bounds = aabb_combine(bounds, calc_bounds(mesh.faces + i++));
	size = bounds.max - bounds.min;
	sizef = 1.0f / fminf(size[0], fminf(size[1], size[2]));
	normalize_faces(mesh, sizef, (t_fvec){
		-(bounds.min[X] + (size[X] / 2)),
		-(bounds.min[Y]),
		-(bounds.min[Z] + (size[Z] / 2))
	});
}

t_parse_err	create_mesh(t_meshdat *data, t_conf_data *conf)
{
	t_mesh	mesh;

	if (!dynarr_finalize(&data->conf.objects))
		return (destroy_meshdata(data, FREE_BOTH, DYNARR));
	if (!add_mtls(&data->conf, conf))
		return (destroy_meshdata(data, FREE_BOTH, DYNARR));
	mesh.name = data->name;
	mesh.faces = data->conf.objects.arr;
	mesh.length = data->conf.objects.length;
	normalize_size(mesh);
	if (!dynarr_addone(&conf->meshes, &mesh))
		return (destroy_meshdata(data, FREE_ALL, DYNARR));
	return (destroy_meshdata(data, FREE_MIN, SUCCESS));
}
