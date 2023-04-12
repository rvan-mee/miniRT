/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_foreach.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 15:07:31 by lsinke        #+#    #+#                 */
/*   Updated: 2022/07/01 15:07:31 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>

void	dynarr_foreach(t_dynarr *arr, void (*f)(void *, void *), void *param)
{
	size_t	index;

	if (arr == NULL || f == NULL)
		return ;
	index = 0;
	while (index < arr->length)
		f(dynarr_get(arr, index++), param);
}
