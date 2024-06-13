/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/09 19:38:23 by lvan-gef      #+#    #+#                 */
/*   Updated: 2023/12/27 00:53:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	int	*_set_input(char **argv, int *args)
{
	int	counter;

	counter = 0;
	while (*argv != NULL)
	{
		args[counter] = to_number(*argv);
		if (args[counter] < 1 || args[counter] > INT_MAX)
		{
			print_error("Not a valid input!\n");
			free(args);
			return (NULL);
		}
		counter++;
		argv++;
	}
	return (args);
}

static int	*_check_input(int argc, char **argv)
{
	int	*args;
	int	counter;

	argv++;
	counter = argc - 1;
	args = malloc(counter * sizeof(int));
	if (args == NULL)
	{
		print_error("Faild to create placeholder for inputs!\n");
		return (NULL);
	}
	return (_set_input(argv, args));
}

int	*check_input(int argc, char **argv)
{
	if (argc < 5)
	{
		print_error("expect at least 4 arguments!\n");
		return (NULL);
	}
	else if (argc > 6)
	{
		print_error("expect at max 5 arguments!\n");
		return (NULL);
	}
	return (_check_input(argc, argv));
}
