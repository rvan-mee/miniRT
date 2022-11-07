#include <minirt.h>
#include <math.h>
#include <ft_math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <render.h>

#define OBJ_N	5000
#define RAY_N	500

typedef enum {
	SPHERE_,
	PLANE_,
	CYLINDER_,
	AABB_,
	END_
}	cidx_t;

static t_object	create_object(cidx_t type, int i)
{
	t_fvec	coords = {0,-5,i};
	t_fvec	orient = {0,0.70710678118,0.70710678118};
	float	param = i * 3 + 0.1f;
	switch (type) {
		case SPHERE_:
			return ((t_object){.coords = coords, .sphere = {param, powf(param / 2, 2)}, .type = SPHERE});
		case PLANE_:
			return ((t_object){.coords = coords, .plane = {orient}, .type = PLANE});
		case CYLINDER_:
			return ((t_object){.coords = coords, .cylinder = {2 * param * orient, orient, param, 2 * param, powf(param / 2, 2)}, .type = CYLINDER});
		default:
			exit(-1);
	}
}

static t_aabb	create_bounds(int i)
{
	t_fvec	coords = {-10, -10, 3};
	t_fvec	size = {i * 2.4f + 1, i / 0.3f + 1, i + 88};
	return ((t_aabb){coords, coords + size});
}

int	main(void)
{
	t_object	**objects = calloc(AABB_, sizeof(t_object *));
	for (int i = SPHERE_; i < AABB_; i++)
		objects[i] = calloc(OBJ_N, sizeof(t_object));
	t_aabb		*bounds = calloc(OBJ_N, sizeof(t_aabb));
	t_ray		ray = {{0,0,0},{0,0,1}};

	for (int i = 0; i < OBJ_N; i++) {
		for (int obj = SPHERE_; obj < AABB_; obj++) {
			objects[obj][i] = create_object(obj, i);
		}
		bounds[i] = create_bounds(i);
	}

	float	min_t = INFINITY;
	clock_t	costs[END_][OBJ_N];
	clock_t	sphere_costs[OBJ_N] = {};
	clock_t	cyl_costs[OBJ_N] = {};
	clock_t	plane_costs[OBJ_N] = {};
	clock_t	aabb_costs[OBJ_N] = {};
	clock_t	time;
	clock_t	prev;
	for (int i = 0; i < RAY_N; i++) {
		time = clock();
		for (int j = 0; j < OBJ_N; j++) {
			prev = time;
			min_t = fminf(min_t, intersect(objects[SPHERE_] + j, &ray));
			sphere_costs[j] += (time = clock()) - prev;
		}
	}
	for (int i = 0; i < RAY_N; i++) {
		time = clock();
		for (int j = 0; j < OBJ_N; j++) {
			prev = time;
			min_t = fminf(min_t, intersect(objects[CYLINDER_] + j, &ray));
			cyl_costs[j] += (time = clock()) - prev;
		}
	}
	for (int i = 0; i < RAY_N; i++) {
		time = clock();
		for (int j = 0; j < OBJ_N; j++) {
			prev = time;
			min_t = fminf(min_t, intersect(objects[PLANE_] + j, &ray));
			plane_costs[j] += (time = clock()) - prev;
		}
	}
	time = clock();
	for (int i = 0; i < RAY_N; i++) {
		for (int j = 0; j < OBJ_N; j++) {
			prev = time;
			min_t = fminf(min_t, aabb_intersect(bounds[j], &ray));
			aabb_costs[j] += (time = clock()) - prev;
		}
	}
	printf("%f %d rays intersected %d objects of each type\n", min_t, RAY_N, OBJ_N);
	time = 0;
	for (int i = 0; i < OBJ_N; i++)
		time += sphere_costs[i];
	printf("SPHERE cycles = %lu (%f each)\n", time, (time / (double) RAY_N) / (float) OBJ_N);
	time = 0;
	for (int i = 0; i < OBJ_N; i++)
		time += plane_costs[i];
	printf("PLANE cycles = %lu (%f each)\n", time, (time / (double) RAY_N) / (float) OBJ_N);
	time = 0;
	for (int i = 0; i < OBJ_N; i++)
		time += cyl_costs[i];
	printf("CYLINDER cycles = %lu (%f each)\n", time, (time / (double) RAY_N) / (float) OBJ_N);
	time = 0;
	for (int i = 0; i < OBJ_N; i++)
		time += aabb_costs[i];
	printf("AABB cycles = %lu (%f each)\n", time, (time / (double) RAY_N) / (float) OBJ_N);
}
