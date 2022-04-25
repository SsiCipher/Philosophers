#include "philo.h"

int print_error(char *error)
{
	if (!error)
		return (0);
	while (*error)
		write(2, error++, 1);
	return (1);
}

int	atoi_check(char *number)
{
	int			i;
	int			sign;
	long long	num;

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
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

int init_data(t_data *data, int argc, char **argv)
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
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philos_count);
	if (!data->philos)
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_error("Error:\nWrong arguments\n"));
	if (!init_data(&data, argc - 1, argv + 1))
		return (print_error("Error:\nFailed to init data\n"));
	return (0);
}
