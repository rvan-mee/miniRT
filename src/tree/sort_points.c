/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_points.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 18:32:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/10 18:32:19 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>
#include <ft_math.h>
#include <libft.h>
#include <rt_tree.h>

static void	*new_tab(uint8_t k, uint32_t length, uint32_t data_size)
{
	uint8_t	dim;
	void	**rv;

	rv = malloc(k * sizeof(void *) + k * length * data_size);
	if (rv == NULL)
		return (NULL);
	dim = 0;
	while (dim < k)
	{
		rv[dim] = (void *)(rv + k) + dim * length * data_size;
		++dim;
	}
	return (rv);
}

static uint32_t	**init_dst(uint32_t length)
{
	uint32_t	**dst;
	uint32_t	n;

	dst = new_tab(4, length, sizeof(uint32_t));
	if (dst == NULL)
		return (NULL);
	n = length;
	while (n--)
		dst[0][n] = n;
	n = 4;
	while (--n)
		ft_memcpy(dst[n], dst[0], length * sizeof(uint32_t));
	return (dst);
}

static int	compare_adapter(void *a, void *b, t_rtdat *data)
{
	const uint32_t	i[2] = {*((uint32_t *) a), *((uint32_t *) b)};
	const t_point	*p_a = data->objs[i[0]];
	const t_point	*p_b = data->objs[i[1]];

	return (compare_points(p_a->pos, p_b->pos, data->dim));
}

static void	sort_dimension(t_rtdat *data)
{
	t_sort	sort;

	sort = (t_sort){
		data->sorted[data->dim],
		sizeof(uint32_t),
		(t_cmp) compare_adapter,
		data
	};
	squicksort(&sort, 0, data->len - 1);
}

// TODO: multithread?
uint32_t	**presort_data(t_point *points[], uint32_t length)
{
	t_rtdat	data;

	data = (t_rtdat){
		points,
		init_dst(length),
		length,
		3
	};
	if (data.sorted == NULL)
		return (NULL);
	while (data.dim--)
		sort_dimension(&data);
	return (data.sorted);
}
