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

bool	render(t_scene *scene, size_t width, size_t height)
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
	return (true);
}