/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quicksort.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 11:16:10 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/12 11:16:10 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>

static void	swapi(int32_t *a, int32_t *b)
{
	int32_t	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int32_t	tri_median(int32_t *arr, uint32_t low, uint32_t high)
{
	uint32_t	mid;

	mid = (low + high) / 2;
	if (arr[mid] < arr[low])
		swapi(arr + mid, arr + low);
	if (arr[high] < arr[low])
		swapi(arr + high, arr + low);
	if (arr[high] < arr[mid])
		swapi(arr + mid, arr + high);
	return (arr[mid]);
}

static uint32_t	partition(int32_t *arr, uint32_t low, uint32_t high)
{
	int32_t	pivot;

	pivot = tri_median(arr, low, high);
	while (low < high)
	{
		while (arr[low] < pivot)
			++low;
		while (arr[high] > pivot)
			--high;
		if (low < high)
			swapi(arr + low, arr + high);
	}
	return (low);
}

void	quicksort(int32_t *arr, uint32_t low, uint32_t high)
{
	uint32_t	partition_index;

	if (low >= high)
		return ;
	if (high - low < INSERTION_SORT_CUTOFF)
		return (inssort(arr, low, high + 1));
	partition_index = partition(arr, low, high);
	if (partition_index != 0)
		quicksort(arr, low, partition_index - 1);
	if (partition_index != high)
		quicksort(arr, partition_index + 1, high);
}
