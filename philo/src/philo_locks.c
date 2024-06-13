/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_locks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/26 01:42:47 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/27 00:51:30 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	*init_lock(void)
{
	pthread_mutex_t	*a_lock;

	a_lock = malloc(sizeof(pthread_mutex_t));
	if (a_lock == NULL)
		return (NULL);
	if (pthread_mutex_init(a_lock, NULL) != 0)
	{
		pthread_mutex_destroy(a_lock);
		free(a_lock);
		return (NULL);
	}
	return (a_lock);
}

void	clear_lock(pthread_mutex_t *a_lock)
{
	pthread_mutex_destroy(a_lock);
	free(a_lock);
}

void	clear_locks(pthread_mutex_t *locks, int size)
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

pthread_mutex_t	*create_locks(int size)
{
	pthread_mutex_t	*locks;
	int				counter;

	locks = malloc(size * sizeof(pthread_mutex_t));
	if (locks == NULL)
	{
		print_error("failed to create holder for locks!\n");
		return (NULL);
	}
	counter = 0;
	while (counter < size)
	{
		if (pthread_mutex_init(&locks[counter], NULL) < 0)
		{
			print_error("Faild to init a lock!\n");
			clear_locks(locks, counter);
			return (NULL);
		}
		counter++;
	}
	return (locks);
}
