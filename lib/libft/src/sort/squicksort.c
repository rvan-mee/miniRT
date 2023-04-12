/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   squicksort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 11:16:10 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/30 11:16:10 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>

static size_t	tri_median(t_sort *sort, size_t low, size_t high)
{
	size_t	mid;

	mid = (low + high) / 2;
	if (cmp(sort, mid, low) < 0)
		swap(sort, mid, low);
	if (cmp(sort, high, mid) < 0)
		swap(sort, high, mid);
	if (cmp(sort, mid, low) < 0)
		swap(sort, mid, low);
	return (mid);
}

static size_t	partition(t_sort *sort, size_t low, size_t high)
{
	size_t	pivot;

	pivot = tri_median(sort, low, high);
	while (low <= high)
	{
		while (cmp(sort, low, pivot) < 0)
			++low;
		while (cmp(sort, pivot, high) < 0)
			--high;
		if (low == high)
			return (low + 1);
		swap(sort, low, high);
		if (pivot == low)
			pivot = high;
		else if (pivot == high)
			pivot = low;
	}
	return (low);
}

void	squicksort(t_sort *sort, size_t low, size_t high)
{
	size_t	partition_idx;

	if (low >= high)
		return ;
	if (high - low < INSERTION_SORT_CUTOFF)
		return (sinssort(sort, low, high + 1));
	partition_idx = partition(sort, low, high);
	if (partition_idx > 0)
		squicksort(sort, low, partition_idx - 1);
	squicksort(sort, partition_idx, high);
}
