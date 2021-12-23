/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascal <alpascal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:41:30 by alpascal          #+#    #+#             */
/*   Updated: 2021/12/23 15:17:02 by alpascal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_diner(t_philos *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&(args->forks[philo->l_fork]));
	ft_print_op(args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(args->forks[philo->r_fork]));
	ft_print_op(args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(args->is_eating));
	ft_print_op(args, philo->id, "is eating");
	philo->t_prev_eat = ft_get_time();
	pthread_mutex_unlock(&(args->is_eating));
	ft_sleepo(args->t_eat, args);
	(philo->nb_eat)++;
	pthread_mutex_unlock(&(args->forks[philo->l_fork]));
	pthread_mutex_unlock(&(args->forks[philo->r_fork]));
}

void	*ft_rout(void *v_philos)
{
	int				i;
	t_philos		*philo;
	t_args			*args;

	i = 0;
	philo = (t_philos *)v_philos;
	args = philo->args;
	if (philo->id % 2)
		usleep(15000);
	while (!(args->ded))
	{
		if (args->stop_eat || (philo->nb_eat >= args->max_eat
				&& args->max_eat != -1))
			break ;
		ft_diner(philo);
		if (args->stop_eat || (philo->nb_eat >= args->max_eat
				&& args->max_eat != -1))
			break ;
		ft_print_op(args, philo->id, "is sleeping");
		ft_sleepo(args->t_sleep, args);
		ft_print_op(args, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_loop(t_args *args, t_philos *philos)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(&(args->forks[philos->l_fork]));
	while (++i < args->nb_philos)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < args->nb_philos)
		pthread_mutex_destroy(&(args->forks[i]));
	pthread_mutex_destroy(&(args->writing));
}	

void	ft_loop_2(t_args *a, t_philos *p)
{
	int	i;

	while (!(a->stop_eat))
	{
		i = -1;
		while (++i < a->nb_philos && !(a->ded))
		{
			pthread_mutex_lock(&(a->is_eating));
			if (ft_time_diff(p[i].t_prev_eat, ft_get_time()) > a->t_death)
			{
				ft_print_op(a, i, "died");
				a->ded = 1;
			}
			pthread_mutex_unlock(&(a->is_eating));
			usleep(100);
		}
		if (a->ded)
			break ;
		i = 0;
		while (a->max_eat != -1 && i < a->nb_philos
			&& p[i].nb_eat >= a->max_eat)
			i++;
		if (i == a->nb_philos)
			a->stop_eat = 1;
	}
}

int	ft_loop(t_args *args)
{
	int				i;
	t_philos		*philo;

	i = 0;
	philo = args->philos;
	args->starting_time = ft_get_time();
	while (i < args->nb_philos)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, ft_rout, &(philo[i])))
			return (1);
		philo[i].t_prev_eat = ft_get_time();
		i++;
	}
	ft_loop_2(args, args->philos);
	exit_loop(args, philo);
	return (0);
}
