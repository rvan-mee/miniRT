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

#include <stddef.h>
#include <parse.h>
#include <libft.h>

#define ARR_COUNT	6

static const size_t	g_arrparams[ARR_COUNT][3] = {\
	{offsetof(t_conf_data, lights), 4, sizeof(t_object)},				\
	{offsetof(t_conf_data, materials), 32, sizeof(t_mtl)},				\
	{offsetof(t_conf_data, objects), 256, sizeof(t_object)},			\
	{offsetof(t_conf_data, vertices), 256, sizeof(t_fvec)},				\
	{offsetof(t_conf_data, vertex_normals), 256, sizeof(t_fvec)},		\
	{offsetof(t_conf_data, vertex_textures), 256, sizeof(t_fvec)}
};

bool	cleanup_parse(void *anything, t_conf_data *data)
{
	t_mtl	*mtl;
	size_t	i;

	free(anything);
	i = 0;
	while (i < data->materials.length)
	{
		mtl = dynarr_get(&data->materials, i++);
		free(mtl->map_Ka.data);
		free(mtl->map_Kd.data);
		free(mtl->map_Ks.data);
		free(mtl->name);
	}
	dynarr_delete(&data->lights);
	dynarr_delete(&data->objects);
	dynarr_delete(&data->vertices);
	dynarr_delete(&data->vertex_textures);
	dynarr_delete(&data->vertex_normals);
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

// This function does really set the scene
void	set_scene(t_scene *scene, t_conf_data *data)
{
	scene->lights = data->lights.arr;
	scene->lights_len = data->lights.length;
	scene->objects = data->objects.arr;
	scene->objects_len = data->objects.length;
	scene->materials = data->materials.arr;
	scene->materials_len = data->materials.length;
	dynarr_delete(&data->vertex_textures);
	dynarr_delete(&data->vertex_normals);
	dynarr_delete(&data->vertices);
}
