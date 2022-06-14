/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:43:41 by yanab             #+#    #+#             */
/*   Updated: 2022/06/13 17:22:47 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (!data->forks)
		return (0);
	while (i < data->philos_count)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
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
		data->philos[i].last_time_eaten = data->start_time;
		data->philos[i].is_eating = 0;
		data->philos[i].is_dead = 0;
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

int	check_error(t_data data, int check_last_arg)
{
	return (
		data.philos_count <= 0
		|| data.time_to_die <= 0
		|| data.time_to_eat <= 0
		|| data.time_to_sleep <= 0
		|| (check_last_arg && data.n_times_to_eat == -1)
	);
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
	if (check_error(*data, argc == 5))
		return (0);
	if (!init_philos(data))
		return (0);
	if (!init_mutexes(data))
		return (0);
	return (1);
}
