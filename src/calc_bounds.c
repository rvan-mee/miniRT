#include <minirt.h>
#include <math.h>
#include <stdlib.h>

static t_aabb	face_bounds(t_object *obj)
{
	const t_face	*f = &obj->face;

	return ((t_aabb) {
		.min = {
			fminf(fminf(f->vert[0][X], f->vert[1][X]), f->vert[2][X]),
			fminf(fminf(f->vert[0][Y], f->vert[1][Y]), f->vert[2][Y]),
			fminf(fminf(f->vert[0][Z], f->vert[1][Z]), f->vert[2][Z]),
		},
		.max = {
			fmaxf(fmaxf(f->vert[0][X], f->vert[1][X]), f->vert[2][X]),
			fmaxf(fmaxf(f->vert[0][Y], f->vert[1][Y]), f->vert[2][Y]),
			fmaxf(fmaxf(f->vert[0][Z], f->vert[1][Z]), f->vert[2][Z]),
		}
	});
}

static t_aabb	cyl_bounds(t_object *obj)
{
	const t_aabb	bot = {
			obj->coords - (obj->cylinder.diameter / 2),
			obj->coords + (obj->cylinder.diameter / 2)
	};
	const t_aabb	top = {
			obj->coords + obj->cylinder.top - (obj->cylinder.diameter / 2),
			obj->coords + obj->cylinder.top + (obj->cylinder.diameter / 2)
	};

	return ((t_aabb) {
		.min = {
			fminf(bot.min[X], top.min[X]),
			fminf(bot.min[Y], top.min[Y]),
			fminf(bot.min[Z], top.min[Z]),
		},
		.max = {
			fmaxf(bot.max[X], top.max[X]),
			fmaxf(bot.max[Y], top.max[Y]),
			fmaxf(bot.max[Z], top.max[Z]),
		}
	});
}

t_aabb	calc_bounds(t_object *obj)
{
	switch (obj->type) {
		case SPHERE:
			return ((t_aabb){
				obj->coords - (obj->sphere.diameter / 2),
				obj->coords + (obj->sphere.diameter / 2)
			});
		case PLANE:
			return ((t_aabb){
				{-10000, -10000, -10000},
				{10000, 10000, 10000}
			});
		case CYLINDER:
			return (cyl_bounds(obj));
		case FACE:
			return (face_bounds(obj));
		default:
		{
			printf("exit in calc_bounds\n");
			exit(2); // todo, i mean cyl n shit
		}
	}
}