/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_mtl.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 17:06:52 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/17 11:18:30 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MTL_H
# define PARSE_MTL_H

typedef enum e_parse_mtl {
	MTL_UNINIT,
	MTL_AMBIENT,
	MTL_DIFFUSE,
	MTL_SPECULAR,
	MTL_EMISSIVE,
	MTL_ILLUMINATION,
	MTL_REFLECTION,
	MTL_TRANSPARENCY1,
	MTL_TRANSPARENCY2,
	MTL_DENSITY,
	MTL_TRFILTER,
	MTL_MAP_KD,
	MTL_MAP_KA,
	MTL_MAP_KS,
	MTL_END
}	t_parse_mtl;

t_parse_err	parse_mtl_ka(char *line, t_object *object);
t_parse_err	parse_mtl_ks(char *line, t_object *object);
t_parse_err	parse_mtl_kd(char *line, t_object *object);
t_parse_err	parse_mtl_ke(char *line, t_object *object);
t_parse_err	parse_mtl_illum(char *line, t_object *object);
t_parse_err	parse_mtl_ns(char *line, t_object *object);
t_parse_err	parse_mtl_d(char *line, t_object *object);
t_parse_err	parse_mtl_tr(char *line, t_object *object);
t_parse_err	parse_mtl_ni(char *line, t_object *object);
t_parse_err	parse_mtl_tf(char *line, t_object *object);
t_parse_err	parse_mtl_map_ka(char *line, t_object *object);
t_parse_err	parse_mtl_map_kd(char *line, t_object *object);
t_parse_err	parse_mtl_map_ks(char *line, t_object *object);

t_parse_err	parse_mtl_map(char *line, t_bmp *bmp);

#endif
