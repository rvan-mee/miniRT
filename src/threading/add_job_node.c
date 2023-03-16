/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_render_lst.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 18:35:59 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/25 18:02:43 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <libft.h>

bool	add_new_job_node(t_threading *thread, t_job func, void *job_param)
{
	static t_jobs	*last_node;
	t_jobs			*new_node;

	new_node = malloc(sizeof(t_jobs));
	if (!new_node)
		return (false);
	new_node->job = func;
	new_node->job_param = job_param;
	new_node->next_job = NULL;
	if (thread->job_lst == NULL)
		thread->job_lst = new_node;
	else
		last_node->next_job = new_node;
	last_node = new_node;
	return (true);
}

void	clear_job_lst(t_threading *thread)
{
	t_jobs	*to_free;
	t_jobs	*to_free_next;

	pthread_mutex_lock(&thread->job_lock);
	to_free = thread->job_lst;
	thread->job_lst = NULL;
	pthread_mutex_unlock(&thread->job_lock);
	while (to_free)
	{
		to_free_next = to_free->next_job;
		free(to_free->job_param);
		free(to_free);
		to_free = to_free_next;
	}
}
