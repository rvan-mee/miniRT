/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_get.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 14:58:44 by lsinke        #+#    #+#                 */
/*   Updated: 2022/07/01 14:58:44 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>

void	*dynarr_get_u(t_dynarr *arr, size_t index)
{
	return (arr->arr + (index * arr->elem_size));
}

void	*dynarr_get(t_dynarr *arr, size_t index)
{
	if (arr == NULL || index >= arr->length)
		return (NULL);
	return (dynarr_get_u(arr, index));
}

void	*dynarr_get_top(t_dynarr *arr)
{
	if (arr == NULL || arr->length == 0)
		return (NULL);
	return (dynarr_get_u(arr, arr->length - 1));
}
