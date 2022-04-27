#include "philo.h"

int	print_error(char *error)
{
	if (!error)
		return (0);
	while (*error)
		write(2, error++, 1);
	return (1);
}

int	atoi_check(char *number)
{
	int i;
	int sign;
	long long num;

	i = 0;
	sign = 1;
	if (number[i] == '-' || number[i] == '+')
		if (number[i++] == '-')
			sign *= -1;
	num = 0;
	while (number[i])
		num = num * 10 + (number[i++] - '0');
	return (sign * num);
}

unsigned long	get_curr_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	custom_sleep(unsigned long time)
{
	unsigned long start_time;

	start_time = get_curr_time();
	while (get_curr_time() - start_time < time)
		usleep(500);
}

int init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (!data->forks)
		return (0);
	while (i < data->philos_count)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philos_count);
	if (!data->philos)
		return (0);
	while (i < data->philos_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].n_times_eaten = 0;
		data->philos[i].last_time_eaten = -1;
		i++;
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->philos_count = atoi_check(argv[0]);
	data->time_to_die = atoi_check(argv[1]);
	data->time_to_eat = atoi_check(argv[2]);
	data->time_to_sleep = atoi_check(argv[3]);
	if (argc == 5)
		data->n_times_to_eat = atoi_check(argv[4]);
	else
		data->n_times_to_eat = -1;
	data->start_time = get_curr_time();
	if (!init_philos(data))
		return (0);
	if (!init_mutexes(data))
		return (0);
	return (1);
}

void	print_msg(int philo_id, int state, t_data data)
{
	unsigned long	timestamp;

	timestamp = get_curr_time() - data.start_time;
	pthread_mutex_lock(&data.write_mutex);
	if (state == TAKEN_FORK)
		printf("%ld %d has taken a fork\n", timestamp, philo_id);
	else if (state == EATING)
		printf("%ld %d is eating\n", timestamp, philo_id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", timestamp, philo_id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", timestamp, philo_id);
	else if (state == DIED)
		printf("%ld %d died\n", timestamp, philo_id);
	pthread_mutex_unlock(&data.write_mutex);
}

void *philo_routine(void *params)
{
	t_data *data;

	data = (t_data *)params;
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_error("Error:\nWrong arguments\n"));
	if (!init_data(&data, argc - 1, argv + 1))
		return (print_error("Error:\nFailed to init data\n"));

	i = 0;
	while (i < data.philos_count)
	{
		pthread_create(&data.philos[i], NULL, philo_routine, &data);
		i++;
	}

	return (0);
}
