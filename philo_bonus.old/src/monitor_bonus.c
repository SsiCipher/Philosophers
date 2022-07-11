/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:18:51 by yanab             #+#    #+#             */
/*   Updated: 2022/07/06 16:35:54 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	time_from(time_t from)
{
	return (from + (get_curr_time() - from));	
}

bool	monitor_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_count)
	{
		// printf("time from: %ld - %ld = %%ld\n", meals_time_diff(data, i), time_from(data->philos[0].last_time_eaten));
		if (
			!data->philos[i].is_eating
			// && meals_time_diff(data, i) > data->time_to_die
			&& time_from(data->philos[i].last_time_eaten) - data->start_time > data->time_to_die
		)
		{
			print_msg(data->philos[i].id, DIED, *data, get_curr_time());
			data->philos[i].is_dead = true;
			return (true);
		}
		usleep(10);
	}
	return (false);
}

bool	monitor_meals_count(t_data *data)
{
	int	i;
	int	philos_done_eating;

	i = -1;
	philos_done_eating = 0;
	while (++i < data->philos_count)
	{
		if (data->philos[i].n_times_eaten >= data->n_times_to_eat)
			philos_done_eating++;
	}
	if (philos_done_eating == data->philos_count)
	{
		printf("All philosophers have eaten %d times\n", data->n_times_to_eat);
		return (true);
	}
	return (false);
}
