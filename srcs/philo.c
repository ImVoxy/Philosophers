/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascal <alpascal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:57:00 by alpascal          #+#    #+#             */
/*   Updated: 2021/12/23 15:16:27 by alpascal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_args *args)
{
	int	i;

	i = args->nb_philos;
	while (--i >= 0)
		if (pthread_mutex_init(&(args->forks[i]), NULL))
			return (1);
	if (pthread_mutex_init(&(args->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(args->is_eating), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_args *args)
{
	int	i;

	i = args->nb_philos;
	while (--i >= 0)
	{
		args->philos[i].id = i;
		args->philos[i].args = args;
		args->philos[i].l_fork = i;
		args->philos[i].r_fork = i + 1;
		if (args->philos[i].r_fork == args->nb_philos)
			args->philos[i].r_fork = 0;
		args->philos[i].t_prev_eat = 0;
		args->philos[i].nb_eat = 0;
	}
	return (0);
}

int	ft_init(t_args *args, char **av)
{
	args->nb_philos = ft_atoi(av[1]);
	args->t_death = ft_atoi(av[2]);
	args->t_eat = ft_atoi(av[3]);
	args->t_sleep = ft_atoi(av[4]);
	args->stop_eat = 0;
	args->ded = 0;
	if (args->t_death < 0 || args->t_eat < 0 || args->nb_philos <= 0
		|| args->t_sleep < 0 || args->nb_philos > 201)
		return (1);
	if (av[5])
	{
		args->max_eat = ft_atoi(av[5]);
		if (args->max_eat < 0)
			return (1);
	}
	else
		args->max_eat = -1;
	if (init_mutex(args))
		return (2);
	init_philosophers(args);
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;
	int		test;

	if (ac < 5 || ac > 6)
	{
		write(2, "Arguments error : 4 or 5 are accepted\n", 38);
		return (1);
	}
	test = ft_init(&args, av);
	if (test)
	{
		if (test == 1)
			write(2, "Arguments error : args must be integers > 0\n", 44);
		else if (test == 2)
			write(2, "Mutex error : couldn't intialize mutex\n", 39);
		return (1);
	}
	else if (ft_loop(&args))
	{
		write(2, "Threads error : couldn't create threads\n", 40);
		return (1);
	}
	return (0);
}
