#include <minirt.h>
#include <math.h>
#include <stdlib.h>

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
		default:
			exit(2); // todo, i mean cyl n shit
	}
}