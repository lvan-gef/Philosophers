/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/10 15:53:06 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/28 01:31:10 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	void	clean_state(pthread_mutex_t *shared_lock,
						pthread_mutex_t *printer_lock,
						t_sim_state *shared_state)
{
	if (shared_state)
		free(shared_state);
	if (printer_lock)
		clear_lock(printer_lock);
	if (shared_lock)
		clear_lock(shared_lock);
}

static	t_sim_state	*shared_state(const int *args, bool rounds)
{
	pthread_mutex_t	*shared_lock;
	pthread_mutex_t	*printer_lock;
	t_sim_state		*shared_state;

	shared_lock = init_lock();
	printer_lock = init_lock();
	shared_state = malloc(sizeof(t_sim_state));
	if (shared_state == NULL || shared_lock == NULL || printer_lock == NULL)
	{
		clean_state(shared_lock, printer_lock, shared_state);
		return (NULL);
	}
	shared_state->running = true;
	shared_state->s_lock = shared_lock;
	shared_state->p_lock = printer_lock;
	shared_state->die_time = args[1];
	shared_state->eat_time = args[2];
	shared_state->sleep_time = args[3];
	shared_state->has_rounds = rounds;
	shared_state->start_stamp = 0;
	shared_state->dead_print = false;
	return (shared_state);
}

static	t_philo	*make_philo(void)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->c_lock = init_lock();
	if (philo->c_lock == NULL)
	{
		free(philo);
		return (NULL);
	}
	philo->s_lock = init_lock();
	if (philo->s_lock == NULL)
	{
		clear_lock(philo->c_lock);
		free(philo);
		return (NULL);
	}
	return (philo);
}

static	bool	set_philos(t_philo **philos,
					const int *args,
					pthread_mutex_t *locks,
					t_sim_state *sim_state)
{
	int	counter;

	counter = 0;
	while (counter < args[0])
	{
		philos[counter] = make_philo();
		if (philos[counter] == NULL)
		{
			free_philos(philos, counter);
			return (false);
		}
		philos[counter]->state = sim_state;
		philos[counter]->id = counter + 1;
		philos[counter]->rounds = 0;
		if (philos[counter]->state->has_rounds)
			philos[counter]->rounds = args[4];
		philos[counter]->l_fork = &locks[get_left_fork(philos[counter]->id)];
		philos[counter]->r_fork = philos[counter]->l_fork;
		if (args[0] > 1)
			philos[counter]->r_fork = &locks[
				get_right_fork(philos[counter]->id, args[0])];
		counter++;
	}
	return (true);
}

t_philo	**create_philos(const int *args, bool rounds, pthread_mutex_t *locks)
{
	t_philo			**philos;
	t_sim_state		*sim_state;

	sim_state = shared_state(args, rounds);
	if (sim_state == NULL)
	{
		print_error("failed to create a shared state\n");
		return (NULL);
	}
	philos = malloc(args[0] * sizeof(t_philo *));
	if (philos == NULL)
	{
		print_error("failed to create a philo's\n");
		clean_state(sim_state->s_lock, sim_state->p_lock, sim_state);
		return (NULL);
	}
	if (set_philos(philos, args, locks, sim_state) == false)
		return (NULL);
	return (philos);
}
