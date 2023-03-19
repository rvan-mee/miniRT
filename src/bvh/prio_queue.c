/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prio_queue.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 03:17:46 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/19 03:17:46 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <bvh.h>

void	init_queue(t_queue *queue)
{
	uint16_t	i;

	queue->pool.next = queue->buf;
	i = 1;
	while (i < QUEUE_LEN)
	{
		queue->buf[i - 1].next = queue->buf + i;
		++i;
	}
	queue->buf[QUEUE_LEN - 1].next = NULL;
}

void	clear_queue(t_queue *queue)
{
	t_prio	*last;
	t_prio	*next;

	last = &queue->queue;
	next = last->next;
	last->next = NULL;
	while (next)
	{
		last = next;
		next = last->next;
		last->next = queue->pool.next;
		queue->pool.next = last;
	}
}

static void	purge_queue(t_queue *queue, t_prio *last)
{
	t_prio	*next;

	next = last->next;
	last->next = NULL;
	while (next)
	{
		last = next;
		next = last->next;
		last->next = queue->pool.next;
		queue->pool.next = last;
	}
}

void	insert(t_queue *queue, t_prio node, bool purge)
{
	t_prio	*insert_after;
	t_prio	*dst;

	insert_after = &queue->queue;
	while (insert_after->next && insert_after->next->dist < node.dist)
		insert_after = insert_after->next;
	dst = queue->pool.next;
	dst->dist = node.dist;
	dst->node = node.node;
	queue->pool.next = dst->next;
	dst->next = insert_after->next;
	insert_after->next = dst;
	if (purge)
		purge_queue(queue, dst);
}
