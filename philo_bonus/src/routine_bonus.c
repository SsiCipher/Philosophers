/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:46:08 by yanab             #+#    #+#             */
/*   Updated: 2022/07/19 03:48:10 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_forks(t_philo *philo)
{
	sem_t	*forks;

	forks = philo->data->forks;
	sem_wait(forks);
	print_msg(philo->id, TAKEN_FORK, *(philo->data), true);
	sem_wait(forks);
	print_msg(philo->id, TAKEN_FORK, *(philo->data), true);
}

void	philo_eat(t_philo *philo, time_t time_to_eat)
{
	sem_t	*forks;

	forks = philo->data->forks;
	print_msg(philo->id, EATING, *(philo->data), true);
	philo->is_eating = true;
	philo->last_time_eaten = get_curr_time();
	philo->n_times_eaten += 1;
	sleep_usec(time_to_eat);
	philo->is_eating = false;
	sem_post(forks);
	sem_post(forks);
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

void	philo_main(t_data *data, int i)
{
	int			time_elapsed;
	pthread_t	child_thread;

	if (pthread_create(&child_thread, NULL, philo_routine, &(data->philos[i])))
		exit(EXIT_FAILURE);
	while (true)
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
			exit(EXIT_FAILURE);
		}
		usleep(100);
	}
}

void	start_philos(t_data *data)
{
	int		i;
	pid_t	child_pid;

	i = 0;
	while (i < data->philos_count)
	{
		child_pid = fork();
		if (child_pid == -1)
			exit(EXIT_FAILURE);
		else if (child_pid == 0)
			philo_main(data, i);
		i += 2;
	}
	i = 1;
	while (i < data->philos_count)
	{
		child_pid = fork();
		if (child_pid == -1)
			exit(EXIT_FAILURE);
		else if (child_pid == 0)
			philo_main(data, i);
		i += 2;
	}
}
