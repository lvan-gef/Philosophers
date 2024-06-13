/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 18:48:23 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/27 23:02:46 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_left_fork(int id)
{
	return (id - 1);
}

int	get_right_fork(int id, int size)
{
	int	right_fork;

	if (id % 2 != 0)
	{
		if (id == 1)
			right_fork = size - 1;
		else if (id == size)
			right_fork = size - 2;
		else
			right_fork = id - 2;
	}
	else
		right_fork = id - 2;
	return (right_fork);
}

bool	_get_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		if (check_state(philo) != true)
		{
			drop_fork(philo);
			return (false);
		}
		print_state(philo, cur_stamp_milli() - philo->state->start_stamp,
			"Taken forks");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		if (check_state(philo) != true)
		{
			drop_fork(philo);
			return (false);
		}
		print_state(philo, cur_stamp_milli() - philo->state->start_stamp,
			"Taken forks");
	}
	return (true);
}

bool	get_fork(t_philo *philo)
{
	if (philo->l_fork == philo->r_fork)
	{
		sleeper(philo->state->die_time + 1, philo, false);
		check_state(philo);
		return (false);
	}
	return (_get_fork(philo));
}

void	drop_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}
