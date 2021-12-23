/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascal <alpascal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:29:44 by alpascal          #+#    #+#             */
/*   Updated: 2021/12/23 15:16:18 by alpascal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

struct	s_rules;

typedef struct s_philos
{
	int					id;
	int					nb_eat;
	int					l_fork;
	int					r_fork;
	long long			t_prev_eat;
	struct s_args		*args;
	pthread_t			thread_id;
}						t_philos;

typedef struct s_args
{
	int					nb_philos;
	int					t_death;
	int					t_eat;
	int					t_sleep;
	int					max_eat;
	int					ded;
	int					stop_eat;
	long long			starting_time;
	pthread_mutex_t		is_eating;
	pthread_mutex_t		forks[202];
	pthread_mutex_t		writing;
	t_philos			philos[202];
}						t_args;

int						ft_atoi(const char *str);
int						ft_loop(t_args *args);
void					ft_print_op(t_args *args, int id, char *string);
void					ft_sleepo(long long time, t_args *args);
void					exit_loop(t_args *args, t_philos *philos);
long long				ft_get_time(void);
long long				ft_time_diff(long long i, long long j);

#endif
