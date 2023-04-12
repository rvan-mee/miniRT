/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_finalize.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 14:40:42 by lsinke        #+#    #+#                 */
/*   Updated: 2022/07/01 14:40:42 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>

bool	dynarr_finalize(t_dynarr *arr)
{
	if (arr == NULL)
		return (false);
	return (dynarr_grow(arr, arr->length));
}
