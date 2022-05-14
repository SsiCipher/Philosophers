#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> // TEST ONLY
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

#define TAKEN_FORK 0
#define EATING 1
#define SLEEPING 2
#define THINKING 3
#define DIED 4

typedef long t_timestamp;

struct s_data;

typedef struct s_philo
{
	unsigned int id;
	int n_times_eaten;
	t_timestamp last_time_eaten;
	pthread_t thread;
	struct s_data *data;
} t_philo;

typedef struct s_data
{
	int philos_count;
	t_timestamp time_to_die;
	t_timestamp time_to_eat;
	t_timestamp time_to_sleep;
	int n_times_to_eat;

	t_timestamp start_time;

	t_philo *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t write_mutex;
} t_data;

// ========> src/init_data.c
int init_mutexes(t_data *data);
int init_philos(t_data *data);
int init_data(t_data *data, int argc, char **argv);

// ========> src/routine.c
void *philo_routine(void *params);

// ========> src/utils.c
int atoi_check(char *number);
t_timestamp get_curr_time();
void sleep_usec(t_timestamp usec);
void print_msg(int philo_id, int state, t_data data);

#endif
