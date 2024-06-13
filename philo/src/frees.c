/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frees.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/10 15:59:57 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/27 04:04:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_philos(t_philo **philos, int size)
{
	int	counter;

	counter = 0;
	while (counter < size)
	{
		if (counter == 0)
		{
			pthread_mutex_destroy(philos[counter]->state->s_lock);
			pthread_mutex_destroy(philos[counter]->state->p_lock);
			free(philos[counter]->state->s_lock);
			free(philos[counter]->state->p_lock);
			free(philos[counter]->state);
		}
		pthread_mutex_destroy(philos[counter]->c_lock);
		free(philos[counter]->c_lock);
		pthread_mutex_destroy(philos[counter]->s_lock);
		free(philos[counter]->s_lock);
		free(philos[counter]);
		counter++;
	}
	free(philos);
}

void	free_locks(pthread_mutex_t *locks, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		pthread_mutex_destroy(&locks[index]);
		index++;
	}
	free(locks);
}
