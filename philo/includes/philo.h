/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:40:56 by yanab             #+#    #+#             */
/*   Updated: 2022/08/15 03:25:29 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKEN_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

struct	s_data;

typedef struct s_philo
{
	unsigned int	id;
	int				n_times_eaten;
	time_t			last_time_eaten;
	bool			is_eating;
	bool			is_dead;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philos_count;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				n_times_to_eat;
	time_t			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	check_mutex;
}	t_data;

// --------> src/init_data.c <--------

bool		init_mutexes(t_data *data);
bool		init_philos(t_data *data);
bool		check_error(t_data data, int check_last_arg);
bool		init_data(t_data *data, int argc, char **argv);

// --------> src/routine.c <--------

void		pick_forks(t_philo *philo);
void		philo_eat(t_philo *philo, time_t time_to_eat);
void		*philo_routine(void *params);

// --------> src/utils.c <--------

int			atoi_check(char *number);
time_t		get_curr_time(void);
void		sleep_usec(time_t usec);
time_t		calc_time_elapsed(t_data *data, int i);
void		print_msg(int philo_id, int state, t_data data, bool unlock_mutex);

// --------> main.c <--------

bool		print_error(char *error);
void		start_philos(t_data *data);
bool		monitor_death(t_data *data);
bool		monitor_meals_count(t_data *data);

#endif
