/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:07 by yanab             #+#    #+#             */
/*   Updated: 2022/07/06 17:23:03 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_error(char *error)
{
	if (!error)
		return (false);
	while (*error)
		write(2, error++, 1);
	return (true);
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

time_t	time_from(time_t from)
{
	return (from + (get_curr_time() - from));	
}

bool	monitor_death(t_data *data)
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
			print_msg(data->philos[i].id, DIED, *data, false);
			data->philos[i].is_dead = 1;
			return (true);
		}
		i++;
		if (i > data->philos_count)
			i = 0;
	}
	return (false);
}

bool	monitor_meals_count(t_data *data)
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
		print_msg(0, DONE, *data, false);
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (print_error("Error:\nWrong arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
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
