/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:40:56 by yanab             #+#    #+#             */
/*   Updated: 2022/06/26 05:42:07 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <string.h>
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

typedef long	t_timestamp;

struct			s_data;

typedef struct s_philo
{
	unsigned int	id;
	int				n_times_eaten;
	t_timestamp		last_time_eaten;
	int				is_eating;
	int				is_dead;
	pthread_t		thread;
	bool			left_fork_picked;
	bool			right_fork_picked;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philos_count;
	t_timestamp		time_to_die;
	t_timestamp		time_to_eat;
	t_timestamp		time_to_sleep;
	int				n_times_to_eat;
	t_timestamp		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
}	t_data;

// --------> src/init_data.c <--------
int			init_mutexes(t_data *data);
int			init_philos(t_data *data);
int			check_error(t_data data, int check_last_arg);
int			init_data(t_data *data, int argc, char **argv);

// --------> src/routine.c <--------
void		philo_sleep(t_philo *philo, t_timestamp time_to_sleep);
void		philo_eat(t_philo *philo, t_timestamp time_to_eat);
void		pick_forks(t_philo *philo);
void		put_forks(t_philo *philo);
void		*philo_routine(void *params);

// --------> src/utils.c <--------
int			atoi_check(char *number);
t_timestamp	get_curr_time(void);
t_timestamp	meals_time_diff(t_data *data, int philo_i);
void		sleep_usec(t_timestamp usec);
void		print_msg(int philo_id, int state, t_data data);

// --------> main.c <--------
int			print_error(char *error);
void		start_philos(t_data *data);
int			monitor_death(t_data *data);
int			monitor_meals_count(t_data *data);

#endif
