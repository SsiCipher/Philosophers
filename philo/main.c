/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:07 by yanab             #+#    #+#             */
/*   Updated: 2022/06/13 17:36:37 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *error)
{
	if (!error)
		return (0);
	while (*error)
		write(2, error++, 1);
	return (1);
}

void	start_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_create(&(data->philos[i].thread), NULL,
			philo_routine, &(data->philos[i]));
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < data->philos_count)
	{
		pthread_create(&(data->philos[i].thread), NULL,
			philo_routine, &(data->philos[i]));
		i += 2;
	}
}

int	monitor_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		if (
			!data->philos[i].is_eating
			&& meals_time_diff(data, i) > data->time_to_die
		)
		{
			print_msg(data->philos[i].id, DIED, *data);
			data->philos[i].is_dead = 1;
			return (1);
		}
		usleep(10);
		i++;
	}
	return (0);
}

int	monitor_meals_count(t_data *data)
{
	int	i;
	int	philos_done_eating;

	i = 0;
	philos_done_eating = 0;
	while (i < data->philos_count)
	{
		if (data->philos[i].n_times_eaten >= data->n_times_to_eat)
			philos_done_eating++;
		i++;
	}
	if (philos_done_eating == data->philos_count)
	{
		printf("All philosophers have eaten %d times\n", data->n_times_to_eat);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (argc < 5 || argc > 6)
		return (print_error("Error:\nWrong arguments\n"));
	if (!init_data(data, argc - 1, argv + 1))
		return (print_error("Error:\nFailed to initialize data\n"));
	start_philos(data);
	while (1)
	{
		if (
			monitor_death(data)
			|| (data->n_times_to_eat != -1 && monitor_meals_count(data))
		)
			return (1);
	}
	return (0);
}
