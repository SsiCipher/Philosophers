/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:43:41 by yanab             #+#    #+#             */
/*   Updated: 2022/07/02 21:59:31 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	init_semaphores(t_data *data)
{
	sem_unlink("/forks_sem");
	sem_unlink("/write_sem");
	sem_unlink("/death_sem");
	data->forks = sem_open("/forks_sem", O_CREAT, 0666, data->philos_count);
	data->write_sem = sem_open("/write_sem", O_CREAT, 0666, 1);
	data->death_sem = sem_open("/death_sem", O_CREAT, 0666, 1);
	return (
		data->forks != SEM_FAILED
		&& data->write_sem != SEM_FAILED
		&& data->death_sem != SEM_FAILED
	);
}

bool	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philos_count);
	if (!data->philos)
		return (false);
	while (i < data->philos_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].pid = 0;
		data->philos[i].n_times_eaten = 0;
		data->philos[i].last_time_eaten = data->start_time;
		data->philos[i].is_eating = 0;
		data->philos[i].is_dead = 0;
		data->philos[i].left_fork_picked = false;
		data->philos[i].right_fork_picked = false;
		data->philos[i].data = data;
		i++;
	}
	return (true);
}

bool	check_error(t_data data, bool check_last_arg)
{
	return (
		data.philos_count <= 0
		|| data.time_to_die <= 0
		|| data.time_to_eat <= 0
		|| data.time_to_sleep <= 0
		|| (check_last_arg && data.n_times_to_eat == -1)
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
	data->start_time = get_curr_time();
	if (check_error(*data, argc == 5))
		return (false);
	if (!init_philos(data))
		return (false);
	if (!init_semaphores(data))
		return (false);
	return (true);
}
