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

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_minirt	t_minirt;
typedef void			(*t_job)(t_minirt *, void *);
typedef int32_t			t_ivec \
__attribute__ ((vector_size (4 * sizeof(int32_t))));
// thanks to norminette this is necessary
typedef const t_ivec	t_civec;

typedef struct s_render_block {
	t_ivec	start;
	t_ivec	size;
}	t_render;

typedef struct s_jobs {
	void			(*job)(t_minirt *, void *);
	t_render		job_param;
	struct s_jobs	*next_job;
}	t_jobs;

typedef struct s_threading
{
	bool			quit;
	bool			stop;
	pthread_cond_t	stop_cond;
	size_t			threads_done;
	pthread_cond_t	done_cond;
	pthread_mutex_t	quit_lock;
	pthread_t		threads[THREAD_C];
	size_t			created_threads;
	t_jobs			*job_lst;
	pthread_mutex_t	job_lock;
	uint64_t		render_start;
}	t_threading;

// add_job_node.c
bool		add_new_job_node(t_threading *thread, t_job func, t_render param);

//	create_render_lst.c
bool		create_render_queue(t_threading *thread, size_t w, size_t h);

//	work.c
void		*work(void *param);

//	work_utils.c
void		quit_working(t_threading *thread);
void		stop_working(t_threading *thread, bool stop);
uint64_t	get_time_ms(void);

//	reset_work.c
void		wait_till_done(t_threading *data);
void		wipe_image(t_minirt *data);
void		clear_job_lst(t_threading *thread);
bool		reset_work(t_minirt *data);

//	threads.c
bool		init_work_threads(t_minirt *data);
void		join_threads(t_minirt *data);

#endif
