/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   binary_search.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 18:21:53 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/11 18:21:53 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

/**
 * Find a value in a sorted array. The array HAS to contain the value
 */
uint32_t	binary_search(const int32_t *arr, int32_t val, uint32_t size)
{
	uint32_t	idx;
	uint32_t	l;
	uint32_t	r;

	l = 0;
	r = size - 1;
	while (l <= r)
	{
		idx = (l + r) / 2;
		if (arr[idx] < val)
			l = idx + 1;
		else if (arr[idx] > val)
			r = idx - 1;
		else
			return (idx);
	}
	return (UINT32_MAX);
}
