/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_delete.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 14:39:51 by lsinke        #+#    #+#                 */
/*   Updated: 2022/07/01 14:39:51 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>
#include <stdlib.h>

void	dynarr_delete(t_dynarr *arr)
{
	if (arr != NULL)
		free(arr->arr);
	arr->arr = NULL;
}
