/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:42:49 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/15 15:42:49 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <get_next_line.h>
#include <unistd.h>
#include <stdio.h>

static void	print_fvec(char *what, t_fvec vec)
{
	printf("%s: %f,%f,%f\t", what, vec[0], vec[1], vec[2]);
}

static void	print_sphere(t_sphere obj)
{
	print_fvec("sphere coords", obj.coords);
	printf("diameter: %f\t", obj.diameter);
	printf("colour: %8X\n", obj.colour.rgba);
}
static void	print_plane(t_plane obj)
{
	print_fvec("plane coords", obj.coords);
	print_fvec("orientation", obj.orientation);
	printf("colour: %8X\n", obj.colour.rgba);
}
static void	print_cylinder(t_cylinder obj)
{
	print_fvec("cylinder coords", obj.coords);
	print_fvec("orientation", obj.orientation);
	printf("diameter: %f\t", obj.diameter);
	printf("height: %f\t", obj.height);
	printf("colour: %8X\n", obj.colour.rgba);
}

int	main(void)
{
	t_scene	scene;
	bool	result = parse_scene(STDIN_FILENO, &scene);
	printf(result ? "true\n" : "false\n");
	print_fvec("camera coords", scene.camera.camera.coords);
	print_fvec("orientation", scene.camera.camera.orientation);
	printf("fov: %u\n", scene.camera.camera.fov);

	printf("ambient ratio: %f\t", scene.ambient.ambient.ratio);
	printf("colour: %8X\n", scene.ambient.ambient.colour.rgba);

	for (size_t i = 0; i < scene.lights_len; i++) {
		printf("light %lu ", i);
		print_fvec("coords", scene.lights[i].coords);
		printf("brightness: %f\t", i, scene.lights[i].brightness);
		printf("colour: %8X\n", scene.lights[i].colour.rgba);
	}

	for (size_t i = 0; i < scene.objects_len; ++i) {
		t_object obj = scene.objects[i];
		switch (obj.type) {
			case SPHERE:
				print_sphere(obj.sphere);
				break ;
			case PLANE:
				print_plane(obj.plane);
				break ;
			case CYLINDER:
				print_cylinder(obj.cylinder);
				break ;
		}
	}
}
