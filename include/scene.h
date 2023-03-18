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

// http://paulbourke.net/dataformats/mtl/
typedef struct s_mtl {
	char 		*name;
	t_fvec		ambient; 		// Ka - ambient colour of material
	t_fvec		diffuse; 		// Kd - diffuse colour
	t_fvec		specular;		// Ks - specular colour
	t_fvec		emmis_col; 		// Ke - emissive colour
	int32_t		illum;   		// illum - lind of illumination
	float		reflec;  		// Ns - specular shininess
	float		transp_d;  		// d - dissolve | tr is the inverse of d ( 1.0 - tr)
	float		transp_tr;  	// Tr - transparency | tr is the inverse of d ( 1.0 - tr)
	float		opt_dens; 		// Ni - optical density
	t_fvec		tra_filter; 	// Tf - Transmission filter
	t_bmp		map_Kd;
	t_bmp		map_Ka;
	t_bmp		map_Ks;
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
	t_fvec		vert[3];
	bool		has_normal;
	t_fvec		normals[3];
	bool		has_texture; // todo: unused? get_texture_face
	t_fvec		uvw[3];
	t_fvec		v0v1;
	t_fvec		v0v2;
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
		t_ambient			ambient;
		t_camera			camera;
		t_light				light;
		t_plane				plane;
		t_sphere			sphere;
		t_cylinder			cylinder;
		t_triangle			triangle;
		t_face				face;
		t_mtl				material;
	};
	t_obj_type	type;
	union {
		t_mtl	*mat;
		size_t	mat_idx;
	};
	bool		has_mat;
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

static inline
bool	is_flag(t_mtl *mtl, t_mtl_flag flags)
{
	return ((mtl->flags & flags) != 0);
}

static inline
void	set_flag(t_mtl *mtl, t_mtl_flag flag)
{
	mtl->flags |= flag;
}

#endif
