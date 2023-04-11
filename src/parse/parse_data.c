/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/11 23:26:34 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/11 23:26:34 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <parse_obj.h>

#define ARR_COUNT	7

static const size_t	g_arrparams[ARR_COUNT][3] = {\
	{offsetof(t_conf_data, lights), 4, sizeof(t_object)},				\
	{offsetof(t_conf_data, materials), 32, sizeof(t_mtl)},				\
	{offsetof(t_conf_data, objects), 256, sizeof(t_object)},			\
	{offsetof(t_conf_data, v), 256, sizeof(t_fvec)},					\
	{offsetof(t_conf_data, vn), 256, sizeof(t_fvec)},					\
	{offsetof(t_conf_data, vt), 256, sizeof(t_fvec)},					\
	{offsetof(t_conf_data, meshes), 4, sizeof(t_mesh)},					\
};

static void	destroy_mesh(t_mesh *mesh, void *ign)
{
	(void) ign;
	free(mesh->name);
	free(mesh->faces);
}

bool	cleanup_parse(void *anything, t_conf_data *data)
{
	free(anything);
	if (data->materials.arr)
		dynarr_foreach(&data->materials, (t_foreach) destroy_mtl, NULL);
	dynarr_delete(&data->lights);
	dynarr_delete(&data->objects);
	dynarr_delete(&data->v);
	dynarr_delete(&data->vt);
	dynarr_delete(&data->vn);
	if (data->meshes.arr)
		dynarr_foreach(&data->meshes, (t_foreach) destroy_mesh, NULL);
	dynarr_delete(&data->meshes);
	dynarr_delete(&data->materials);
	return (false);
}

bool	init_parse(t_conf_data *data, int32_t fd)
{
	const size_t	*p;
	uint8_t			i;

	ft_bzero(data, sizeof(t_conf_data));
	i = 0;
	while (i < ARR_COUNT)
	{
		p = g_arrparams[i++];
		if (!dynarr_create((t_dynarr *)((void *)data + p[0]), p[1], p[2]))
			return (cleanup_parse(NULL, data));
	}
	data->fd = fd;
	data->exposure = -1.0f;
	return (true);
}

// If we do this while parsing, the pointers will be invalidated whenever the
// array grows.
static void	set_mtl_pointers(t_object *obj, t_conf_data *data)
{
	if (obj->mat_idx == SIZE_MAX)
		obj->mat = NULL;
	else
		obj->mat = dynarr_get(&data->materials, obj->mat_idx - 1);
}

// This function does really set the scene
void	set_scene(t_scene *scene, t_conf_data *data)
{
	scene->lights = data->lights.arr;
	scene->lights_len = data->lights.length;
	scene->objects = data->objects.arr;
	scene->objects_len = data->objects.length;
	scene->materials = data->materials.arr;
	scene->materials_len = data->materials.length;
	dynarr_delete(&data->vt);
	dynarr_delete(&data->vn);
	dynarr_delete(&data->v);
	dynarr_foreach(&data->objects, (t_foreach) set_mtl_pointers, data);
	dynarr_foreach(&data->meshes, (t_foreach) destroy_mesh, NULL);
	dynarr_delete(&data->meshes);
}
