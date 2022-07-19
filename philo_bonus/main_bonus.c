/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:07 by yanab             #+#    #+#             */
/*   Updated: 2022/07/19 03:34:35 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	print_error(char *error)
{
	if (!error)
		return (false);
	while (*error)
		write(2, error++, 1);
	return (true);
}

void	kill_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_count)
		kill(data->philos[i].pid, SIGKILL);
	exit(EXIT_FAILURE);
}

// UNUSED
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

// UNUSED
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
	int		status;

	if (argc != 5 && argc != 6)
		return (print_error("Error:\nWrong arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!init_data(data, argc - 1, argv + 1))
		return (print_error("Error:\nFailed to initialize data\n"));
	data->start_time = get_curr_time();
	start_philos(data);
	while (waitpid(-1, &status, 0) != -1)
	{
		if (status > 0)
			exit(EXIT_SUCCESS);
	}
	return (0);
}
