/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 00:19:58 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/27 05:50:15 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_sim_state
{
	bool			running;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int64_t			start_stamp;
	pthread_mutex_t	*p_lock;
	pthread_mutex_t	*s_lock;
	bool			has_rounds;
	bool			dead_print;
}	t_sim_state;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*c_lock;
	pthread_mutex_t	*s_lock;
	int				rounds;
	int64_t			stop_stamp;
	t_sim_state		*state;
}	t_philo;

// src/fork_utils.c
int				get_left_fork(int id);
int				get_right_fork(int id, int size);
bool			get_fork(t_philo *philo);
void			drop_fork(t_philo *philo);

// src/frees.c
void			free_philos(t_philo **philos, int size);
void			free_locks(pthread_mutex_t *locks, int size);

// src/init_philos.c
t_philo			**create_philos(const int *args,
					bool rounds,
					pthread_mutex_t *locks);

// src/input_check.c
int				*check_input(int argc, char **argv);

// src/main.c
int				main(int argc, char **argv);

// src/philo_locks.c
pthread_mutex_t	*init_lock(void);
void			clear_lock(pthread_mutex_t *a_lock);
pthread_mutex_t	*create_locks(int size);
void			clear_locks(pthread_mutex_t *locks, int size);

// src/printers.c
void			printer(const char *msg, pthread_mutex_t p_lock);
void			print_error(char *msg);
void			print_state(t_philo *philo, int64_t timestamp, const char *msg);

// src/sim.c
void			*run_sim(void *data);
bool			check_state(t_philo *philo);

// src/threading.c
pthread_t		*create_threads(t_philo **philos, int size);
void			clean_threads(pthread_t *threads, int size);

// src/utils.c
int				to_number(char *str);
void			sleeper(int sleep_time, t_philo *philo, bool check_it);
int64_t			cur_stamp_milli(void);

#endif
