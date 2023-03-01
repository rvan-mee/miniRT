/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 14:40:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/09 19:48:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <minirt.h>

// add_job_node.c
bool	add_new_job_node(\
	t_minirt *data, \
	void (*func)(t_minirt *, void *), \
	void *job_param);

//	create_render_lst.c
bool	create_render_queue(t_minirt *data);

//	work.c
void	*work(void *param);

//	work_utils.c
void	wait_for_new_job(t_minirt *data);
bool	keep_working(t_threading *thread);
void	quit_working(t_minirt *data);

//	reset_work.c
void	wait_till_done(t_minirt *data);
void	wipe_image(t_minirt *data);
void	clear_job_lst(t_minirt *data);
bool	reset_work(t_minirt *data);

//	threads.c
bool	init_work_threads(t_minirt *data);
void	join_threads(t_minirt *data);

#endif
