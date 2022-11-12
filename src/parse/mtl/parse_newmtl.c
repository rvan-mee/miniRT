/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_newmtl.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 18:16:39 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/12 21:35:15 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <minirt.h>
#include <libft.h>
#include <parse_mtl.h>
#include <get_next_line.h>

static t_parse_error	(*g_parse_mtl[])(char *, t_object *, t_conf_data *) = {\
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
	[MTL_MAP_KA] = parse_mtl_map_ka,							\
	[MTL_MAP_KS] = parse_mtl_map_ks,							\
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

static bool	parse_mtl_name(char *line, t_object *object, t_conf_data *conf)
{
	const t_mtl *mtl_arr = conf->materials.arr;
	size_t		name_len;
	size_t		i;

	i = 0;
	skip_spaces(&line);
	if (!(ft_isalpha(*line) && !ft_isdigit(*line)) && *line != '_')
		return (NAME);
	while (ft_isalpha(line[name_len]) || ft_isdigit(line[name_len]) || line[name_len] == '_')
		name_len++;
	object->material.name = ft_substr(line, 0, name_len);
	if (!object->material.name)
		return (ALLOC);
	line += name_len;
	skip_spaces(&line);
	if (*line)
		return (free(object->material.name), NAME);
	while (i++ < conf->materials.length)
		if (!ft_strncmp(object->material.name, mtl_arr[i].name, name_len + 1))
			return (free(object->material.name), DUP);
	return (SUCCESS);
}

static t_parse_error	mtl_parse_func(char *line, t_obj_type *object, t_conf_data *conf)
{
	t_parse_mtl		type;
	t_parse_error	err;
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
			return (g_parse_mtl[type](line, object, conf));
		}
	}
	return (MTL_ERR);
}

t_parse_error	parse_newmtl(char **linep, t_object *object, t_conf_data *conf)
{
	t_parse_mtl	err;
	char		*line;

	ft_bzero(&object->material.is_enabled, sizeof(t_mtl_enabled));
	if (!parse_mtl_name(*linep, object, conf))
		return (MTL);
	while (1)
	{
		line = get_next_line(conf->fd);
		if (!line)
			break ;
		err = mtl_parse_func(line, object, conf);	
		free(line);
		if (err == SUCCESS)
			break ;
		if (err != CONTINUE) // TODO: free current material
			return (err);
	}
	if (!dynarr_addone(&conf->materials, &object->material)) // TODO: free current material
		return (DYNARR);
	*linep = line;
	return (SUCCESS);
}
