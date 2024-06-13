/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/10 15:50:31 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/27 05:57:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	to_number(char *str)
{
	int	number;

	number = 0;
	if (str == NULL)
		return (number);
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			number *= 10;
			number += *str - '0';
		}
		else
			return (-1);
		str++;
	}
	return (number);
}

int64_t	cur_stamp_milli(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
	{
		print_error("Failed to get the time\n");
		exit(1);
	}
	return (((int64_t)(tv.tv_sec) * 1000) + ((int64_t)(tv.tv_usec) / 1000));
}

void	sleeper(int sleep_time, t_philo *philo, bool check_it)
{
	int64_t	end_time;

	end_time = cur_stamp_milli() + sleep_time;
	while (end_time > cur_stamp_milli())
	{
		usleep(100);
		if (check_it == true && check_state(philo) != true)
			break ;
	}
}
