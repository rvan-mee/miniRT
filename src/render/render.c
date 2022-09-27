/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:32:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/27 15:30:21 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <libft.h>

uint32_t	get_hit_colour(t_scene *scene, t_object *object, t_hit *hit);

bool	shade(t_scene *scene, t_dynarr *hits, uint32_t *pixels)
{
	size_t	i;
	size_t	pixel_index;
	t_hit	*hit;

	(void) scene;
	hit = hits->arr;
	i = hits->length;
	while (i--)
	{
		pixel_index = hit[i].screen_x + hit[i].screen_y * WIDTH;
		pixels[pixel_index] = get_hit_colour(scene, hit[i].object, &hit[i]);
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
	dynarr_delete(&hits);
	free(pixels);
	return (true);
}
