/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_obj.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:36:10 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/18 22:36:10 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_OBJ_H
# define PARSE_OBJ_H
# include <parse.h>

typedef enum e_parse_error	t_perr;
typedef enum e_meshdata_destruction_options {
	FREE_MIN = 0b00,
	FREE_ALL = 0b01,
	FREE_MTL = 0b10,
	FREE_BOTH = 0b11
}	t_md_flags;

typedef struct s_meshdata {
	char		*name;
	t_conf_data	conf;
}	t_meshdat;

typedef struct s_mesh {
	char		*name;
	t_object	*faces;
	size_t		length;
}	t_mesh;

typedef struct s_meshparams {
	char	*name;
	t_fvec	coords;
	t_fvec	w;
	t_fvec	v;
	t_fvec	u;
	float	scale;
}	t_meshparams;

t_perr	init_meshdata(char *path, t_meshdat *dst);
t_perr	destroy_meshdata(t_meshdat *data, t_md_flags flags, t_parse_err err);
t_perr	create_mesh(t_meshdat *data, t_conf_data *conf);
t_perr	add_mesh(t_meshparams params, t_conf_data *conf);

#endif
