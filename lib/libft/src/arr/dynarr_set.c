/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_set.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 15:00:24 by lsinke        #+#    #+#                 */
/*   Updated: 2022/07/01 15:00:24 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>
#include <libft.h>

bool	dynarr_set(t_dynarr *arr, size_t index, const void *obj)
{
	if (arr == NULL)
		return (false);
	if (index >= arr->capacity)
		if (dynarr_grow(arr, index + 1) == false)
			return (false);
	ft_memcpy(dynarr_get_u(arr, index), obj, arr->elem_size);
	return (true);
}
