/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_newmtl.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 18:16:39 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/19 12:18:19 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
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

static t_parse_error	mtl_parse_func(char *line, t_object *object)
{
	t_parse_mtl	type;
	size_t		len;

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
	return (SUCCESS);
}

static t_parse_error	check_dup(t_conf_data *data, char *name)
{
	const size_t	len = ft_strlen(name);
	t_mtl			*mtl;
	size_t			i;

	i = 0;
	while (i < data->materials.length)
	{
		mtl = dynarr_get(&data->materials, i++);
		if (ft_strncmp(name, mtl->name, len + 1) == 0)
			return (DUP);
	}
	return (CONTINUE);
}

//TODO: Add more properties that are required for certain illum modes?
static bool	check_properties(t_mtl *mtl)
{
	static const t_mtl_flag	req = \
		AMBIENT_C | \
		DIFFUSE_C | \
		SPECULAR_C | \
		SPECULAR_EXP;

	return (is_flag(mtl, req));
}

static t_parse_error	err_cleanup(t_mtl *mtl, t_parse_error err)
{
	free(mtl->map_Ka.data);
	free(mtl->map_Kd.data);
	free(mtl->map_Ks.data);
	free(mtl->name);
	return (err);
}

t_parse_error	parse_newmtl(char **linep, t_object *object, t_conf_data *conf)
{
	t_parse_error	err;
	char			*line;
	t_mtl			*mtl;

	mtl = &object->material;
	err = parse_mtl_name(linep, &mtl->name);
	if (err != SUCCESS)
		return (err);
	err = check_dup(conf, mtl->name);
	while (err == CONTINUE)
	{
		line = get_next_line(conf->fd);
		if (!line)
			break ;
		conf->curr_line++;
		err = mtl_parse_func(line, object);
		free(line);
	}
	if (err != SUCCESS)
		return (err_cleanup(mtl, err));
	if (!dynarr_addone(&conf->materials, mtl))
		return (err_cleanup(mtl, DYNARR));
	if (!check_properties(mtl))
		return (err_cleanup(mtl, MTL_ERR));
	return (SUCCESS);
}
