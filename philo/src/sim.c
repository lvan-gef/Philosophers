/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sim.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/25 00:31:18 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 20:11:52 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	bool	eater(t_philo *philo, const t_sim_state *shared_state)
{
	if (check_state(philo) != true)
		return (false);
	if (get_fork(philo) != true)
		return (false);
	print_state(philo,
		cur_stamp_milli() - shared_state->start_stamp, "is eating");
	pthread_mutex_lock(philo->s_lock);
	philo->stop_stamp = cur_stamp_milli() + shared_state->die_time;
	pthread_mutex_unlock(philo->s_lock);
	sleeper(shared_state->eat_time, philo, false);
	drop_fork(philo);
	return (true);
}

static	void	counter(t_philo *philo, const t_sim_state *shared_state)
{
	if (shared_state->has_rounds)
	{
		pthread_mutex_lock(philo->c_lock);
		philo->rounds--;
		pthread_mutex_unlock(philo->c_lock);
	}
}

bool	check_state(t_philo *philo)
{
	bool	alive;

	pthread_mutex_lock(philo->state->s_lock);
	pthread_mutex_lock(philo->s_lock);
	alive = cur_stamp_milli() <= philo->stop_stamp;
	pthread_mutex_unlock(philo->s_lock);
	if (!philo->state->running || !alive)
	{
		if (!alive && !philo->state->dead_print)
		{
			philo->state->running = false;
			philo->state->dead_print = true;
			pthread_mutex_lock(philo->state->p_lock);
			printf("%ld %d died\n",
				cur_stamp_milli() - philo->state->start_stamp, philo->id);
			pthread_mutex_unlock(philo->state->p_lock);
		}
		pthread_mutex_unlock(philo->state->s_lock);
		return (false);
	}
	pthread_mutex_unlock(philo->state->s_lock);
	return (true);
}

void	*run_sim(void *data)
{
	t_philo		*philo;
	static t_sim_state	*shared_state;

	philo = data;
	shared_state = philo->state;
	philo->stop_stamp = shared_state->start_stamp + philo->state->die_time;
	while (1)
	{
		if (eater(philo, shared_state) != true)
			break ;
		if (check_state(philo) != true)
			break ;
		print_state(philo,
			cur_stamp_milli() - shared_state->start_stamp, "is sleeping");
		sleeper(shared_state->sleep_time, philo, true);
		if (check_state(philo) != true)
			break ;
		print_state(philo,
			cur_stamp_milli() - shared_state->start_stamp, "is thinking");
		counter(philo, shared_state);
	}
	return (NULL);
}
