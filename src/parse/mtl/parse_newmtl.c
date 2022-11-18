/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_newmtl.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 18:16:39 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 20:09:03 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <minirt.h>
#include <libft.h>
#include <parse_mtl.h>
#include <get_next_line.h>

static t_parse_error	(*g_parse_mtl[])(char *, t_object *) = {\
	[MTL_AMBIENT] = parse_mtl_ka,								\
	[MTL_DIFFUSE] = parse_mtl_kd,								\
	[MTL_SPECULAR] = parse_mtl_ks,								\
	[MTL_EMISSIVE] = parse_mtl_ke,								\
	[MTL_ILLUMINATION] = parse_mtl_illum,						\
	[MTL_REFLECTION] = parse_mtl_ns,							\
	[MTL_TRANSPARENCY1] = parse_mtl_d,							\
	[MTL_TRANSPARENCY2] = parse_mtl_tr,							\
	[MTL_DENSITY] = parse_mtl_ni,								\
	[MTL_TRFILTER] = parse_mtl_tf,								\
	[MTL_MAP_KD] = parse_mtl_map_kd,							\
	[MTL_MAP_KS] = parse_mtl_map_ks,							\
	[MTL_MAP_KA] = parse_mtl_map_ka,							\
};

static const char		*g_ids[] = {\
	[MTL_AMBIENT] = "Ka",										\
	[MTL_DIFFUSE] = "Kd",										\
	[MTL_SPECULAR] = "Ks",										\
	[MTL_EMISSIVE] = "Ke",										\
	[MTL_ILLUMINATION] = "illum",								\
	[MTL_REFLECTION] = "Ns",									\
	[MTL_TRANSPARENCY1] = "d",									\
	[MTL_TRANSPARENCY2] = "Tr",									\
	[MTL_DENSITY] = "Ni",										\
	[MTL_TRFILTER] = "Tf",										\
	[MTL_MAP_KD] = "map_Kd",									\
	[MTL_MAP_KA] = "map_Ka",									\
	[MTL_MAP_KS] = "map_Ks",									\
};

static t_parse_error	parse_mtl_name(char **linep, \
						t_object *object, t_conf_data *conf)
{
	const t_mtl	*mtl_arr = conf->materials.arr;
	char		*line;
	size_t		name_len;
	size_t		i;

	i = 0;
	line = *linep;
	name_len = 0;
	skip_spaces(&line);
	if (!(ft_isalnum(*line)) && *line != '_')
		return (NAME);
	while (ft_isalnum(line[name_len]) || line[name_len] == '_')
		name_len++;
	object->material.name = ft_substr(line, 0, name_len);
	if (!object->material.name)
		return (ALLOC);
	line += name_len;
	skip_spaces(&line);
	if (*line)
		return (free(object->material.name), NAME);
	while (i < conf->materials.length)
		if (!ft_strncmp(object->material.name, mtl_arr[i++].name, name_len + 1))
			return (free(object->material.name), DUP);
	*linep = line;
	return (SUCCESS);
}

static t_parse_error	mtl_parse_func(char *line, t_object *object)
{
	t_parse_mtl		type;
	size_t			len;

	if (line[0] == '\n')
		return (SUCCESS);
	skip_spaces(&line);
	type = MTL_UNINIT;
	while (++type != MTL_END)
	{
		len = ft_strlen(g_ids[type]);
		if (ft_strncmp(line, g_ids[type], len) == 0)
		{
			line += len;
			return (g_parse_mtl[type](line, object));
		}
	}
	return (MTL_ERR);
}

static void	clear_maps(t_object *obj)
{
	free(obj->material.map_Ka.name);
	free(obj->material.map_Ka.data);
	free(obj->material.map_Kd.name);
	free(obj->material.map_Kd.data);
	free(obj->material.map_Ks.name);
	free(obj->material.map_Ks.data);
}

t_parse_error	parse_newmtl(char **linep, t_object *object, t_conf_data *conf)
{
	t_parse_error	err;
	char			*line;

	ft_bzero(&object->material.is_enabled, sizeof(t_mtl_enabled));
	ft_bzero(&object->material.map_Ka, sizeof(t_bmp));
	ft_bzero(&object->material.map_Kd, sizeof(t_bmp));
	ft_bzero(&object->material.map_Ks, sizeof(t_bmp));
	if (parse_mtl_name(linep, object, conf) != SUCCESS)
		return (MTL_ERR);
	while (1)
	{
		line = get_next_line(conf->fd);
		if (!line)
			break ;
		conf->curr_line++;
		err = mtl_parse_func(line, object);
		free(line);
		if (err == SUCCESS)
			break ;
		if (err != CONTINUE)
			return (clear_maps(object), free(object->material.name), err);
	}
	if (!dynarr_addone(&conf->materials, &object->material))
		return (clear_maps(object), free(object->material.name), DYNARR);
	return (SUCCESS);
}
