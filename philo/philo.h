#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // TEST ONLY
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKEN_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

typedef struct s_philo
{
	unsigned int	id;
	int				n_times_eaten;
	int				last_time_eaten;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				philos_count;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				n_times_to_eat;
	unsigned long	start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
}	t_data;

#endif
