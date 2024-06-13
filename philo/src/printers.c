/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/26 01:43:22 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/27 00:47:26 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	size_t	ft_strlen(const char *msg)
{
	size_t	size;

	size = 0;
	if (msg == NULL)
		return (size);
	while (msg[size] != '\0')
		size++;
	return (size);
}

void	printer(const char *msg, pthread_mutex_t p_lock)
{
	pthread_mutex_lock(&p_lock);
	printf("%s\n", msg);
	pthread_mutex_unlock(&p_lock);
}

void	print_state(t_philo *philo, int64_t timestamp, const char *msg)
{
	pthread_mutex_lock(philo->state->s_lock);
	if (philo->state->running)
	{
		pthread_mutex_lock(philo->state->p_lock);
		printf("%ld %d %s\n", timestamp, philo->id, msg);
		pthread_mutex_unlock(philo->state->p_lock);
	}
	pthread_mutex_unlock(philo->state->s_lock);
}

void	print_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
}
