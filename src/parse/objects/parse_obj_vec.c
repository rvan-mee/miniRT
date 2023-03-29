/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_obj_vec.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/12 00:39:29 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/13 15:57:44 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <ft_math.h>
#include <math.h>

static const t_parse_err	g_errs[] = {\
	[VERTEX] = VERT,					\
	[VT_NORMAL] = NORMAL,				\
	[VT_TEXTURE] = VERT_TEXTURE
};

static uint8_t	parse_values(char **linep, t_fvec *dst)
{
	uint8_t	count;
	char	*line;
	char	*end;

	count = 0;
	line = *linep;
	skip_spaces(&line);
	while (count < 4)
	{
		(*dst)[count] = ft_strtof(line, &end);
		if (line == end)
			return (0);
		line = end;
		if (*line == '\n' || !ft_isspace(*line))
			break ;
		++line;
		++count;
	}
	if (*line != '\n' && *line != '\0')
		return (0);
	*linep = line;
	return (count);
}

static const uint8_t		g_val_lims[][2] = {\
	[VERTEX] = {2, 3},		\
	[VT_TEXTURE] = {0, 2},	\
	[VT_NORMAL] = {2, 2}	\
};

static const t_fvec			g_default_vec[] = {\
	[VERTEX] = {0, 0, 0, 1},	\
	[VT_TEXTURE] = {},			\
	[VT_NORMAL] = {}			\
};

static t_fvec	wrap_texture(t_fvec uvw)
{
	uint8_t	index;

	index = 0;
	while (index < 3)
	{
		if (uvw[index] < 0.0f || uvw[index] < 1.0f)
		{
			uvw[index] = fmodf(uvw[index], 1.0f);
			if (uvw[index] < 0.0f)
				uvw[index] += 1.0f;
		}
		++index;
	}
	return (uvw);
}

t_parse_err	parse_obj_vec(char **linep, t_object *object, t_conf_data *conf)
{
	const t_dynarr		*arrs[] = {\
		[VERTEX] = &conf->v,		\
		[VT_TEXTURE] = &conf->vt,	\
		[VT_NORMAL] = &conf->vn		\
	};
	const t_obj_type	type = object->type;
	uint8_t				value_count;
	t_fvec				dst;

	dst = g_default_vec[type];
	value_count = parse_values(linep, &dst);
	if (value_count < g_val_lims[type][0] || value_count > g_val_lims[type][1])
		return (g_errs[object->type]);
	if (object->type == VT_NORMAL)
		dst = normalize_vector(dst);
	else if (object->type == VT_TEXTURE)
		dst = wrap_texture(dst);
	if (!dynarr_addone((t_dynarr *) arrs[type], &dst))
		return (DYNARR);
	return (SUCCESS);
}
