/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_add.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 14:48:43 by lsinke        #+#    #+#                 */
/*   Updated: 2022/07/01 18:38:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>
#include <libft.h>

static size_t	get_growth(t_dynarr *arr, size_t count)
{
	if (count > arr->capacity)
		return (arr->capacity + count);
	return (arr->capacity * 2);
}

bool	dynarr_add(t_dynarr *arr, const void *objs, size_t count)
{
	if (arr == NULL || objs == NULL)
		return (false);
	if (arr->capacity - arr->length < count)
		if (dynarr_grow(arr, get_growth(arr, count)) == false)
			return (false);
	ft_memcpy(dynarr_get_u(arr, arr->length), objs, count * arr->elem_size);
	arr->length += count;
	return (true);
}

bool	dynarr_addone(t_dynarr *arr, const void *obj)
{
	return (dynarr_add(arr, obj, 1));
}
