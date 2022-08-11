/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:46:08 by yanab             #+#    #+#             */
/*   Updated: 2022/08/11 02:32:22 by yanab            ###   ########.fr       */
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

	sem_wait(philo->data->check_sem);
	philo->is_eating = true;
	sem_post(philo->data->check_sem);
	sem_wait(philo->data->check_sem);
	philo->last_time_eaten = get_curr_time();
	sem_post(philo->data->check_sem);
	sem_wait(philo->data->check_sem);
	philo->n_times_eaten += 1;
	sem_post(philo->data->check_sem);
	
	sleep_usec(time_to_eat);

	sem_wait(philo->data->check_sem);
	philo->is_eating = false;
	sem_post(philo->data->check_sem);

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
		if (
			philo->data->n_times_to_eat != -1
			&& philo->n_times_eaten >= philo->data->n_times_to_eat
		)
			exit(EXIT_SUCCESS);
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
	time_t		last_eaten;
	bool		is_eating;

	if (pthread_create(&child_thread, NULL, philo_routine, &(data->philos[i])))
		exit(EXIT_FAILURE);
	while (true)
	{
		sem_wait(data->check_sem);
		last_eaten = data->philos[i].last_time_eaten;
		sem_post(data->check_sem);
		if (!last_eaten)
			time_elapsed = get_curr_time() - data->start_time;
		else
			time_elapsed = get_curr_time() - last_eaten;
		sem_wait(data->check_sem);
		is_eating = data->philos[i].is_eating;
		sem_post(data->check_sem);
		if (!is_eating && time_elapsed >= data->time_to_die)
		{
			print_msg(data->philos[i].id, DIED, *data, false);
			sem_wait(data->check_sem);
			data->philos[i].is_dead = 1;
			sem_post(data->check_sem);
			exit(EXIT_FAILURE);
		}
		usleep(200);
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
