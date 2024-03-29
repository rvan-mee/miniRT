/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 17:39:28 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/16 17:39:28 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include <minirt.h>
# include <bvh.h>
# include <dynarr.h>
# include <bmp.h>

typedef enum e_object_type {
	UNINITIALIZED = 0,
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
	COMMENT,
	VT_TEXTURE,
	VT_NORMAL,
	VERTEX,
	FACE,
	MTL,
	USEMTL,
	EXPOSURE,
	OBJFILE,
	USEMESH,
	MTLLIB,
	OBJ_GROUP,
	OBJ_OBJ,
	OBJ_SMOOTH,
	END
}	t_obj_type;

typedef enum e_mtl_flag {
	AMBIENT_C = 1,
	DIFFUSE_C = 2,
	SPECULAR_C = 4,
	EMMISIVE_C = 8,
	ILLUM_MODE = 16,
	SPECULAR_EXP = 32,
	DISSOLVED = 64,
	TRANSPARENT = 128,
	REFRACT_IDX = 256,
	TRANSMISSION_FILTER = 512,
	AMBIENT_MAP = 1024,
	DIFFUSE_MAP = 2048,
	SPECULAR_MAP = 4096
}	t_mtl_flag;

/**
 * http://paulbourke.net/dataformats/mtl/
 *
 * ambient:		Ka - ambient colour of material
 * diffuse:		Kd - diffuse colour
 * specular:	Ks - specular colour
 * emmis_col:	Ke - emissive colour
 * illum:		illum - kind of illumination
 * reflec:		Ns - specular shininess
 * transp_d:	d - dissolve | tr is the inverse of d ( 1.0 - tr)
 * transp_tr:	Tr - transparency | tr is the inverse of d ( 1.0 - tr)
 * opt_dens:	Ni - optical density
 * tra_filter:	Tf - transmission filter
 * map_Kd:		diffuse colour texture
 * map_Ka:		ambient colour texture
 * map_Ks:		specular colour texture
 * flags:		flags, signifying which attributes can be used
 */
typedef struct s_mtl {
	char		*name;
	t_fvec		ambient;
	t_fvec		diffuse;
	t_fvec		specular;
	t_fvec		emmis_col;
	int32_t		illum;
	float		reflec;
	float		transp_d;
	float		transp_tr;
	float		opt_dens;
	t_fvec		tra_filter;
	t_bmp		ambient_tex;
	t_bmp		diffuse_tex;
	t_bmp		specular_tex;
	t_mtl_flag	flags;
}	t_mtl;

typedef struct s_ambient {
	float	ratio;
}	t_ambient;

typedef struct s_camera {
	t_fvec	orientation;
	t_fvec	rotated;
	float	rotation[2];
	float	fov;
	t_fvec	u;
	t_fvec	v;
	t_fvec	proj_vec;
	float	exposure;
}	t_camera;

typedef struct s_light {
	float	brightness;
}	t_light;

typedef struct s_sphere {
	float	diameter;
	float	radius_sq;
}	t_sphere;

typedef struct s_triangle {
	t_fvec	vert[3];
	t_fvec	v0v1;
	t_fvec	v0v2;
}	t_triangle;

typedef struct s_face {
	t_fvec	vert[3];
	t_fvec	normals[3];
	t_fvec	uvw[3];
	t_fvec	v0v1;
	t_fvec	v0v2;
	bool	has_normal;
	bool	has_texture;
}	t_face;

/**
 * A infinitely big plane (not aero)
 *
 * `orientation' is the normal of the planes' surface. This means that checking
 * for collision is pretty easy; if a line is perpendicular to the normal, the
 * plane is not hit!
 */
typedef struct s_plane {
	t_fvec	orientation;
}	t_plane;

typedef struct s_cylinder {
	t_fvec	top;
	t_fvec	orientation;
	float	diameter;
	float	height;
	float	radius_sq;
}	t_cylinder;

typedef struct s_object {
	t_fvec		coords;
	t_fvec		colour;
	union {
		t_ambient	ambient;
		t_camera	camera;
		t_light		light;
		t_plane		plane;
		t_sphere	sphere;
		t_cylinder	cylinder;
		t_triangle	triangle;
		t_face		face;
	};
	union {
		t_mtl	*mat;
		size_t	mat_idx;
	};
	t_obj_type	type;
}	t_object;

typedef struct s_scene {
	t_object	camera;
	t_object	ambient;
	t_object	*lights;
	size_t		lights_len;
	t_object	*objects;
	size_t		objects_len;
	t_bvh		bvh;
	t_mtl		*materials;
	size_t		materials_len;
	float		scale;
}	t_scene;

void	get_scene_scale(t_scene *scene);
void	destroy_scene(t_scene *scene);
void	destroy_mtl(t_mtl *mtl, void *ign);
void	calc_ray_info(t_camera *cam, size_t w, size_t h);

static inline
bool	is_flag(const t_mtl *mtl, t_mtl_flag flags)
{
	return (mtl != NULL && ((mtl->flags & flags) != 0));
}

static inline
void	set_flag(t_mtl *mtl, t_mtl_flag flag)
{
	mtl->flags |= flag;
}

#endif
