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
#include <render.h>
#include <libft.h>

static bool	lst_add(t_jobs **head, t_jobs *new)
{
	t_jobs	*tmp;

	tmp = *head;
	if (!new)
		return (false);
	if (!tmp)
	{
		*head = new;
		return (true);
	}
	while (tmp->next_job)
		tmp = tmp->next_job;
	tmp->next_job = new;
	return (true);
}

bool	add_new_job_node(t_minirt *data, t_job func, void *job_param)
{
	t_jobs		*new_node;

	new_node = malloc(sizeof(t_jobs));
	if (!new_node)
		return (false);
	new_node->job = func;
	new_node->job_param = job_param;
	new_node->next_job = NULL;
	lst_add(&data->thread.job_lst, new_node);
	return (true);
}
