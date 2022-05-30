/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:07 by yanab             #+#    #+#             */
/*   Updated: 2022/05/24 15:39:09 by yanab            ###   ########.fr       */
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
		pthread_create(&(data->philos[i].thread), NULL, philo_routine, &(data->philos[i]));
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < data->philos_count)
	{
		pthread_create(&(data->philos[i].thread), NULL, philo_routine, &(data->philos[i]));
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
			&& get_curr_time() - data->philos[i].last_time_eaten > data->start_time + data->time_to_die
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

	i = 0;
	while (
		i < data->philos_count
		&& data->philos[i].n_times_eaten <= data->n_times_to_eat
	)
		i++;
	if (i == data->philos_count)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	// pthread_t	eat_times_thread;

	data = (t_data *)malloc(sizeof(t_data));
	if (argc < 5 || argc > 6)
		return (print_error("Error:\nWrong arguments\n"));
	if (!init_data(data, argc - 1, argv + 1))
		return (print_error("Error:\nFailed to initialize data\n"));
	start_philos(data);
	// if (data->n_times_to_eat != -1)
	// {
	// 	pthread_create(&eat_times_thread, NULL, monitor_meals_count, NULL);
	// 	pthread_detach(eat_times_thread);
	// }
	while (1)
	{
		if (monitor_death(data))
			return (0);
	}
	return (0);
}
