/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:32:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/21 18:32:19 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <libft.h>

static uint32_t	get_colour(t_object *object)
{
	switch (object->type) {
		case SPHERE:
			return (object->sphere.colour.rgba);
		case PLANE:
			return (object->plane.colour.rgba);
		case CYLINDER:
			return (object->cylinder.colour.rgba);
		default:
			return (0);
	}
}

bool	shade(t_scene *scene, t_dynarr *hits, uint32_t *pixels)
{
	size_t	i;
	t_hit	*hit;

	(void) scene;
	hit = hits->arr;
	i = hits->length;
	while (i--)
	{
		pixels[hit[i].screen_x + hit[i].screen_y * WIDTH] = get_colour(hit[i].object);
	}
	return (true);
}

bool	render(t_mlx_data *mlx, t_scene *scene, size_t width, size_t height)
{
	uint32_t	*pixels;
	t_dynarr	hits;

	if (!dynarr_create(&hits, width * height / 2, sizeof(t_hit)))
		return (false);
	if (!cast_primary_rays(scene, width, height, &hits))
		return (false); // TODO: dynarr_delete(&hits);
	pixels = ft_calloc(width * height, sizeof(uint32_t));
	if (!pixels)
		return (false);
	if (!shade(scene, &hits, pixels))
		return (false);
	ft_memcpy(mlx->img->pixels, pixels, width * height * sizeof(uint32_t));
	return (true);
}