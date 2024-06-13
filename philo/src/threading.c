/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threading.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/09 19:20:44 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/27 00:37:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clean_threads(pthread_t *threads, int size)
{
	int	index;
	int	result;

	index = 0;
	while (index < size)
	{
		result = pthread_join(threads[index], NULL);
		if (result != 0)
		{
			print_error("Failed to join a thread!\n");
			break ;
		}
		index++;
	}
	free(threads);
}

pthread_t	*create_threads(t_philo **philos, int size)
{
	int			result;
	int			counter;
	pthread_t	*threads;

	counter = 0;
	threads = malloc(size * sizeof(pthread_t));
	if (threads == NULL)
	{
		print_error("Failed to create a placeholder for threads\n");
		return (NULL);
	}
	while (counter < size)
	{
		result = pthread_create(&threads[counter], NULL,
				run_sim, philos[counter]);
		if (result != 0)
		{
			printer("Failed to create a thread!\n", *philos[0]->state->p_lock);
			clean_threads(threads, counter);
			return (NULL);
		}
		counter++;
	}
	return (threads);
}
