/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 12:59:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/30 12:59:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define INSERTION_SORT_CUTOFF	10

typedef int	(*t_cmp)(void *a, void *b, void *arg);

typedef struct s_sort_data {
	void	*arr;
	size_t	data_size;
	t_cmp	cmp;
	void	*arg;
}	t_sort;

void	quicksort(int32_t *arr, uint32_t low, uint32_t high);
void	squicksort(t_sort *sort, size_t low, size_t high);

void	inssort(int32_t *arr, uint32_t low, uint32_t high);
void	sinssort(t_sort *sort, size_t low, size_t high);

static inline void	swap(t_sort *s, size_t a, size_t b)
{
	size_t	n;
	uint8_t	*pa;
	uint8_t	*pb;
	uint8_t	tmp;

	n = s->data_size;
	pa = s->arr + a * n;
	pb = s->arr + b * n;
	while (n--)
	{
		tmp = *pa;
		*pa++ = *pb;
		*pb++ = tmp;
	}
}

static inline int	cmp(t_sort *s, size_t a, size_t b)
{
	a *= s->data_size;
	b *= s->data_size;
	return (s->cmp(s->arr + a, s->arr + b, s->arg));
}

#endif