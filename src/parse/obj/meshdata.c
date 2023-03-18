/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meshdata.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:38:12 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/18 22:38:12 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse_obj.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

bool	destroy_meshdata(t_meshdat *data, bool free_all, bool free_mtl)
{
	close(data->conf.fd);
	if (free_all)
	{
		free(data->name);
		dynarr_delete(&data->conf.objects);
	}
	dynarr_delete(&data->conf.v);
	dynarr_delete(&data->conf.vt);
	dynarr_delete(&data->conf.vn);
	if (free_mtl)
		dynarr_foreach(&data->conf.materials, (t_foreach) destroy_mtl, NULL);
	dynarr_delete(&data->conf.materials);
	return (false);
}

static bool	get_name(char *path, char **dst)
{
	size_t	len;
	char	*start;

	len = ft_strlen(path) - 4;
	start = ft_strrchr(path, '/');
	if (start != NULL)
		start++;
	else
		start = path;
	len -= start - path;
	*dst = malloc(len + 1);
	if (!*dst)
		return (false);
	ft_memcpy(*dst, start, len);
	(*dst)[len] = '\0';
	return (true);
}

// todo: error messages? idk bro
bool	init_meshdata(char *path, t_meshdat *dst)
{
	ft_bzero(dst, sizeof(t_meshdat));
	if (!check_extension(path, ".obj") || \
		!open_file(path, &dst->conf.fd))
		return (false);
	if (!get_name(path, &dst->name))
		return (destroy_meshdata(dst, false, false));
	if (!dynarr_create(&dst->conf.v, 256, sizeof(t_fvec)) || \
		!dynarr_create(&dst->conf.vt, 256, sizeof(t_fvec)) || \
		!dynarr_create(&dst->conf.vn, 256, sizeof(t_fvec)) || \
		!dynarr_create(&dst->conf.objects, 256, sizeof(t_object)) || \
		!dynarr_create(&dst->conf.materials, 8, sizeof(t_mtl)))
		return (destroy_meshdata(dst, true, false));
	return (true);
}
