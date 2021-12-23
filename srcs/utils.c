/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascal <alpascal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:41:52 by alpascal          #+#    #+#             */
/*   Updated: 2021/12/23 14:54:14 by alpascal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	long int	val;
	int			sign;

	val = 0;
	sign = 1;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			val = val * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(val * sign));
}

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	ft_time_diff(long long i, long long j)
{
	return (j - i);
}

void	ft_sleepo(long long time, t_args *args)
{
	long long	i;

	i = ft_get_time();
	while (!(args->ded))
	{
		if (ft_time_diff(i, ft_get_time()) >= time)
			break ;
		usleep(50);
	}
}

void	ft_print_op(t_args *args, int id, char *str)
{
	pthread_mutex_lock(&(args->writing));
	if (!(args->ded))
	{
		printf("%lli ", ft_get_time() - args->starting_time);
		printf("%i %s\n", id + 1, str);
	}
	pthread_mutex_unlock(&(args->writing));
	return ;
}
