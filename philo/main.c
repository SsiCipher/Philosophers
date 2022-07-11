/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:07 by yanab             #+#    #+#             */
/*   Updated: 2022/07/11 02:34:06 by cipher           ###   ########.fr       */
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

bool	monitor_meals_count(t_data *data)
{
	int	i;

	if (data->n_times_to_eat == -1)
		return (false);
	i = -1;
	while (++i < data->philos_count)
	{
		if (data->philos[i].n_times_eaten < data->n_times_to_eat)
			return (false);
	}
	print_msg(0, DONE, *data, false);
	return (true);
}

bool	monitor_death(t_data *data)
{
	int		i;
	time_t	time_elapsed;

	i = 0;
	while (!monitor_meals_count(data))
	{
		if (data->philos[i].last_time_eaten == 0)
			time_elapsed = get_curr_time() - data->start_time;
		else
			time_elapsed = get_curr_time() - data->philos[i].last_time_eaten;
		if (
			!data->philos[i].is_eating
			&& time_elapsed >= data->time_to_die
		)
		{
			print_msg(data->philos[i].id, DIED, *data, false);
			data->philos[i].is_dead = 1;
			return (true);
		}
		i++;
		if (i >= data->philos_count)
			i = 0;
	}
	return (false);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (print_error("Error:\nWrong arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!init_data(data, argc - 1, argv + 1))
		return (print_error("Error:\nFailed to initialize data\n"));
	data->start_time = get_curr_time();
	start_philos(data);
	return (monitor_death(data));
}
