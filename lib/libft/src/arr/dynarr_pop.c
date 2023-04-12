/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_pop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 19:19:51 by lsinke        #+#    #+#                 */
/*   Updated: 2022/07/11 19:19:51 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>

void	*dynarr_pop(t_dynarr *arr)
{
	if (arr == NULL || arr->length == 0)
		return (NULL);
	return (dynarr_get_u(arr, --arr->length));
}
