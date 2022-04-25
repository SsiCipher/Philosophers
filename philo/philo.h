#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // TEST ONLY
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	unsigned int	id;
	int				n_times_to_eaten;
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
}	t_data;

#endif
