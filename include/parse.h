/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:54:09 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 13:32:53 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <scene.h>

typedef struct s_bmp	t_bmp;

typedef enum e_parse_error {
	SUCCESS,
	OBJECT,
	COORD,
	VECTOR,
	COLOUR,
	FORMAT,
	LRATIO,
	FOV,
	BRIGHT,
	DIAMETER,
	OBJ_HEIGHT,
	INDEX,
	VERT,
	VERT_TEXTURE,
	NORMAL,
	DYNARR,
	MTL_ERR,
	NAME,
	DUP,
	ALLOC,
	KA,
	KD,
	KS,
	KE,
	ILLUM,
	NS,
	D,
	TR,
	NI,
	TF,
	DUPLICATE,
	MATCH,
	TEX_EXT,
	MTL_EXT,
	OBJ_EXT,
	BMP_ERR,
	NON_EXIST,
	CONTINUE,
	EXPOS,
	INV_OBJ,
	INV_MTL,
	OBJ_NF,
	MTL_NF,
	INV_SCALE,
}	t_parse_err;

typedef struct s_conf_data
{
	t_dynarr	lights;
	t_dynarr	objects;
	t_dynarr	v;
	t_dynarr	vt;
	t_dynarr	vn;
	t_dynarr	materials;
	t_dynarr	meshes;
	bool		has_mtl;
	size_t		curr_mtl;
	size_t		curr_line;
	int32_t		fd;
	float		exposure;
}	t_conf_data;

bool		parse_config_file(int32_t argc, char *argv[], t_scene **scene);
bool		parse_scene(int32_t fd, t_scene *dst);
bool		parse_object(char *line, t_object *object, t_conf_data *conf);
t_parse_err	parse_ambient(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_camera(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_light(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_sphere(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_plane(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_cylinder(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_triangle(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_obj_vec(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_face(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_usemtl(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_newmtl(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_exposure(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_mtl_name(char **linep, char **name);
t_parse_err	parse_objfile(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_usemesh(char **linep, t_object *object, t_conf_data *conf);
t_parse_err	parse_mtlfile(char **linep, t_object *object, t_conf_data *conf);
bool		parse_rgb(char **linep, t_fvec *colour);
bool		parse_line_error(const char *line, t_parse_err err, size_t line_c);
void		skip_spaces(char **linep);
void		skip_digits(char **linep);
bool		parse_vector(char **linep, t_fvec *vector, bool normalized);
bool		parse_float(char **linep, float *dst, float min, float max);
bool		parse_float_rgb(char **linep, t_fvec *rgb);
bool		check_extension(const char *config_file, char *ext);
bool		open_file(const char *path, int32_t *fd);
bool		read_file(int32_t fd, void *buf, size_t n_bytes);
bool		write_file(int32_t fd, void *buf, size_t n_bytes);
bool		parse_bmp(char *path, t_bmp *dst);
bool		init_parse(t_conf_data *data, int32_t fd);
void		set_scene(t_scene *scene, t_conf_data *data);
bool		cleanup_parse(void *anything, t_conf_data *data);

#endif
