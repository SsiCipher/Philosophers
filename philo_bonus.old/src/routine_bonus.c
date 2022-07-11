/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:46:08 by yanab             #+#    #+#             */
/*   Updated: 2022/07/05 19:58:20 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_forks(t_philo *philo)
{
	sem_t	*forks;

	forks = philo->data->forks;
	sem_wait(forks);
	philo->left_fork_picked = true;
	print_msg(philo->id, TAKEN_FORK, *(philo->data), get_curr_time());
	sem_wait(forks);
	philo->right_fork_picked = true;
	print_msg(philo->id, TAKEN_FORK, *(philo->data), get_curr_time());
}

void	philo_eat(t_philo *philo, time_t time_to_eat)
{
	sem_t	*forks;

	forks = philo->data->forks;
	print_msg(philo->id, EATING, *(philo->data), get_curr_time());
	philo->is_eating = true;
	philo->last_time_eaten = get_curr_time() - philo->data->start_time;
	philo->n_times_eaten += 1;
	sleep_usec(time_to_eat);
	philo->is_eating = false;
	sem_post(forks);
	sem_post(forks);
}

void	philo_sleep(t_philo *philo, time_t time_to_sleep)
{
	print_msg(philo->id, SLEEPING, *(philo->data), get_curr_time());
	sleep_usec(time_to_sleep);
}

void	*routine(void *params)
{
	t_philo	*philo;

	philo = (t_philo *)params;
	while (true)
	{
		pick_forks(philo);
		philo_eat(philo, philo->data->time_to_eat);
		philo_sleep(philo, philo->data->time_to_sleep);
		print_msg(philo->id, THINKING, *(philo->data), get_curr_time());
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	t_data		*data;
	pthread_t	routine_thread;

	data = philo->data;
	if (pthread_create(&routine_thread, NULL, routine, philo) != 0)
		exit(EXIT_FAILURE);
	while (true)
	{
		if (
			monitor_death(data)
			|| (data->n_times_to_eat != -1 && monitor_meals_count(data))
		)
			kill_all(data);
	}
}
