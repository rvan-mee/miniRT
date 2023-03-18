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

bool		init_meshdata(char *path, t_meshdat *dst);
bool		destroy_meshdata(t_meshdat *data, bool free_all, bool free_mtl);
bool		create_mesh(t_meshdat *data, t_conf_data *conf);
t_parse_err	add_mesh(t_meshparams params, t_conf_data *conf);

#endif
