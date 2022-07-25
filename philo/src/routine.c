/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:46:08 by yanab             #+#    #+#             */
/*   Updated: 2022/07/18 21:40:33 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->data->forks;
	pthread_mutex_lock(&forks[(philo->id - 1) % philo->data->philos_count]);
	print_msg(philo->id, TAKEN_FORK, *(philo->data), true);
	pthread_mutex_lock(&forks[philo->id % philo->data->philos_count]);
	print_msg(philo->id, TAKEN_FORK, *(philo->data), true);
}

void	philo_eat(t_philo *philo, time_t time_to_eat)
{
	pthread_mutex_t	*forks;

	forks = philo->data->forks;
	print_msg(philo->id, EATING, *(philo->data), true);
	philo->is_eating = true;
	philo->last_time_eaten = get_curr_time();
	philo->n_times_eaten += 1;
	sleep_usec(time_to_eat);
	philo->is_eating = false;
	pthread_mutex_unlock(&forks[(philo->id - 1) % philo->data->philos_count]);
	pthread_mutex_unlock(&forks[philo->id % philo->data->philos_count]);
}

void	*philo_routine(void *params)
{
	t_philo	*philo;

	philo = (t_philo *)params;
	while (!(philo->is_dead))
	{
		pick_forks(philo);
		philo_eat(philo, philo->data->time_to_eat);
		print_msg(philo->id, SLEEPING, *(philo->data), true);
		sleep_usec(philo->data->time_to_sleep);
		print_msg(philo->id, THINKING, *(philo->data), true);
	}
	return (NULL);
}
