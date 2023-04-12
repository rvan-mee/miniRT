/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_grow.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 14:42:15 by lsinke        #+#    #+#                 */
/*   Updated: 2022/07/01 14:42:15 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>
#include <libft.h>

bool	dynarr_grow(t_dynarr *arr, size_t new_size)
{
	void	*new_arr;

	if (arr == NULL)
		return (false);
	if (arr->capacity == new_size)
		return (true);
	new_arr = ft_realloc(arr->arr,
			arr->capacity * arr->elem_size,
			new_size * arr->elem_size);
	if (new_arr == NULL)
		return (false);
	arr->arr = new_arr;
	arr->capacity = new_size;
	if (new_size < arr->length)
		arr->length = new_size;
	return (true);
}
