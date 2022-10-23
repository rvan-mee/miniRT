/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 14:40:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/21 13:20:06 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <minirt.h>

void	join_threads(t_minirt *data);
bool	init_work_threads(t_minirt *data);
bool	keep_working(t_threading *thread);
bool	reset_work(t_minirt *data);
void	wipe_image(t_minirt *data);
void	*work(void *param);
void	quit_working(t_minirt *data);
void	destroy_mutexes(t_minirt *data);
void	free_job_node(t_jobs *jobs);
bool	create_work(t_minirt *data);
t_jobs	*get_and_remove_first_node_from_list(t_jobs **head);

#endif
