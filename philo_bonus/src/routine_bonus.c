/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:46:08 by yanab             #+#    #+#             */
/*   Updated: 2022/07/02 22:00:27 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep(t_philo *philo, time_t time_to_sleep)
{
	print_msg(philo->id, SLEEPING, *(philo->data));
	sleep_usec(time_to_sleep);
}

void	philo_eat(t_philo *philo, time_t time_to_eat)
{
	sem_t	*forks;

	forks = philo->data->forks;
	print_msg(philo->id, EATING, *(philo->data));
	philo->is_eating = 1;
	philo->last_time_eaten = get_curr_time() - philo->data->start_time;
	philo->n_times_eaten += 1;
	sleep_usec(time_to_eat);
	philo->is_eating = 0;
	sem_post(forks);
	sem_post(forks);
}

void	pick_forks(t_philo *philo)
{
	sem_t	*forks;

	forks = philo->data->forks;
	sem_wait(forks);
	philo->left_fork_picked = true;
	print_msg(philo->id, TAKEN_FORK, *(philo->data));
	sem_wait(forks);
	philo->right_fork_picked = true;
	print_msg(philo->id, TAKEN_FORK, *(philo->data));
}

void	*routine(void *params)
{
	t_philo	*philo;

	philo = (t_philo *)params;
	while (true)
	{
		pick_forks(philo);
		if (philo->left_fork_picked && philo->right_fork_picked)
		{
			philo_eat(philo, philo->data->time_to_eat);
			philo_sleep(philo, philo->data->time_to_sleep);
			print_msg(philo->id, THINKING, *(philo->data));
		}
	}
	return (NULL);
}

bool	monitor_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_count)
	{
		if (
			!data->philos[i].is_eating
			&& meals_time_diff(data, i) > data->time_to_die
		)
		{
			print_msg(data->philos[i].id, DIED, *data);
			data->philos[i].is_dead = 1;
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

void	philo_routine(t_philo *philo)
{
	t_data		*data;
	pthread_t	routine_thread;

	data = philo->data;
	if (pthread_create(&routine_thread, NULL, routine, philo) != 0)
		exit(EXIT_FAILURE);
	while (!(philo->is_dead))
	{
		if (
			monitor_death(data)
			|| (data->n_times_to_eat != -1 && monitor_meals_count(data))
		)
			exit(EXIT_FAILURE);
	}
	pthread_join(routine_thread, NULL);
}
