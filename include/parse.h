/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:54:09 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/12 21:35:32 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <minirt.h>

#define U 0
#define V 1

typedef struct s_bmp t_bmp;
typedef float t_float_rgb[3];
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
	CONTINUE
}	t_parse_error;

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

typedef struct s_conf_data
{
	t_dynarr	lights;
	t_dynarr	objects;
	t_dynarr	vertices;
	t_dynarr	vertex_textures;
	t_dynarr	vertex_normals;
	t_dynarr	materials;
	int32_t		fd;
}	t_conf_data;

bool			parse_config_file(int32_t argc, char *argv[], t_scene *scene);
bool			parse_scene(int32_t fd, t_scene *dst);
bool			parse_object(char *line, t_object *object, t_conf_data *conf);
t_parse_error	parse_ambient(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_camera(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_light(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_sphere(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_plane(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_cylinder(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_triangle(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_vertex(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_vt(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_vn(char **linep, t_object *object, t_conf_data *conf);
t_parse_error	parse_face(char **linep, t_object *object, t_conf_data *conf);
bool			parse_rgb(char **linep, t_rgba *colour);
bool			parse_line_error(const char *line, t_parse_error err);
void			skip_spaces(char **linep);
void			skip_digits(char **linep);
bool			parse_vector(char **linep, t_fvec *vector, bool normalized);
bool			parse_float(char **linep, float *dst, float min, float max);
bool			parse_float_rgb(char **linep, t_fvec *rgb);
void			normalize(t_scene *scene);
void			normalize_coords(t_scene *scene);
void			normalize_orientation(t_scene *scene);
bool			check_extension(const char *config_file, char *ext);
bool			open_file(const char *path, int32_t *fd);
t_bmp			*parse_bmp(char *path);

#endif
