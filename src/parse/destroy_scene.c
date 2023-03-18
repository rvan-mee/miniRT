/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_mtl.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:22:30 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/18 22:22:30 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <scene.h>
#include <stdlib.h>

void	destroy_mtl(t_mtl *mtl, void *ign)
{
	(void) ign;
	free(mtl->name);
	free(mtl->map_Ka.data);
	free(mtl->map_Kd.data);
	free(mtl->map_Ks.data);
}

void	destroy_scene(t_scene *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->materials_len)
		destroy_mtl(scene->materials + i++, NULL);
	free(scene->materials);
	free(scene->lights);
	free(scene->objects);
	free(scene->bvh.clusters);
	free(scene);
}
