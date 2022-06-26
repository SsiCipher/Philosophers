/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:43:41 by yanab             #+#    #+#             */
/*   Updated: 2022/06/26 05:46:51 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// init philos and semaphores
	return (1);
}
