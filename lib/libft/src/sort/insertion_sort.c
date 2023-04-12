/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   insertion_sort.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 11:16:10 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/30 11:16:10 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>

void	inssort(int32_t *arr, uint32_t low, uint32_t high)
{
	uint32_t	i;
	uint32_t	j;
	int32_t		v;

	i = low + 1;
	while (i < high)
	{
		v = arr[i];
		j = i;
		while (j-- > low && arr[j] > v)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = v;
		++i;
	}
}

void	sinssort(t_sort *sort, size_t low, size_t high)
{
	size_t	i;
	size_t	j;

	i = low + 1;
	while (i < high)
	{
		j = i;
		while (j > low && cmp(sort, j - 1, j) > 0)
		{
			swap(sort, j - 1, j);
			--j;
		}
		++i;
	}
}
