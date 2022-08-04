/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:43:41 by yanab             #+#    #+#             */
/*   Updated: 2022/07/18 21:40:31 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (!data->forks)
		return (false);
	i = -1;
	while (++i < data->philos_count)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->check_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	return (true);
}

bool	init_philos(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philos_count);
	if (!data->philos)
		return (false);
	i = -1;
	while (++i < data->philos_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].n_times_eaten = 0;
		data->philos[i].last_time_eaten = 0;
		data->philos[i].is_eating = false;
		data->philos[i].is_dead = false;
		data->philos[i].data = data;
	}
	return (true);
}

bool	check_error(t_data data, int check_last_arg)
{
	return (
		data.philos_count <= 0
		|| data.time_to_die <= 0
		|| data.time_to_eat <= 0
		|| data.time_to_sleep <= 0
		|| (check_last_arg && data.n_times_to_eat <= 0)
	);
}

bool	init_data(t_data *data, int argc, char **argv)
{
	data->philos_count = atoi_check(argv[0]);
	data->time_to_die = atoi_check(argv[1]);
	data->time_to_eat = atoi_check(argv[2]);
	data->time_to_sleep = atoi_check(argv[3]);
	if (argc == 5)
		data->n_times_to_eat = atoi_check(argv[4]);
	else
		data->n_times_to_eat = -1;
	if (check_error(*data, argc == 5))
		return (false);
	if (!init_philos(data))
		return (false);
	if (!init_mutexes(data))
		return (false);
	return (true);
}
