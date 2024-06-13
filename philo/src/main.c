/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 00:24:12 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/28 01:33:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	bool	more_food(t_philo **philos, int size)
{
	int		index;

	index = 0;
	while (index < size)
	{
		pthread_mutex_lock(philos[index]->c_lock);
		if (philos[index]->rounds > 0)
		{
			pthread_mutex_unlock(philos[index]->c_lock);
			return (true);
		}
		pthread_mutex_unlock(philos[index]->c_lock);
		index++;
	}
	return (false);
}

static	void	monitor(t_philo **philos, const int *args)
{
	while (1)
	{
		pthread_mutex_lock(philos[0]->state->s_lock);
		if (philos[0]->state->running != true)
		{
			pthread_mutex_unlock(philos[0]->state->s_lock);
			break ;
		}
		pthread_mutex_unlock(philos[0]->state->s_lock);
		if (philos[0]->state->has_rounds)
		{
			if (more_food(philos, args[0]) == false)
			{
				pthread_mutex_lock(philos[0]->state->s_lock);
				philos[0]->state->running = false;
				pthread_mutex_unlock(philos[0]->state->s_lock);
				break ;
			}
		}
		sleeper(100, philos[0], false);
	}
}

static	int	clean_up(int *args, pthread_mutex_t *locks,
					t_philo **philos, int exit_code)
{
	if (args == NULL)
		return (exit_code);
	if (locks != NULL)
		free_locks(locks, args[0]);
	if (philos != NULL)
		free_philos(philos, args[0]);
	free(args);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_philo			**philos;
	int				*args;
	pthread_mutex_t	*locks;
	bool			rounds;
	pthread_t		*threads;

	args = check_input(argc, argv);
	if (args == NULL)
		return (EXIT_FAILURE);
	locks = create_locks(args[0]);
	if (locks == NULL)
		return (clean_up(args, NULL, NULL, EXIT_FAILURE));
	rounds = false;
	if (argc == 6)
		rounds = true;
	philos = create_philos(args, rounds, locks);
	if (philos == NULL)
		return (clean_up(args, locks, NULL, EXIT_FAILURE));
	philos[0]->state->start_stamp = cur_stamp_milli();
	threads = create_threads(philos, args[0]);
	if (threads == NULL)
		return (clean_up(args, locks, philos, EXIT_FAILURE));
	monitor(philos, args);
	clean_threads(threads, args[0]);
	return (clean_up(args, locks, philos, EXIT_SUCCESS));
}
