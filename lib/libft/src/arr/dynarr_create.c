/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dynarr_create.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 14:32:14 by lsinke        #+#    #+#                 */
/*   Updated: 2022/07/01 14:32:14 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dynarr.h>
#include <libft.h>

bool	dynarr_create(t_dynarr *ptr, size_t init_size, const size_t data_size)
{
	if (ptr == NULL || data_size == 0)
		return (false);
	*(size_t *) &ptr->elem_size = data_size;
	ptr->capacity = init_size;
	ptr->length = 0;
	ptr->arr = ft_calloc(init_size, data_size);
	return (ptr->arr != NULL);
}
