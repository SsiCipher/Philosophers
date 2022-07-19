/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 06:29:48 by yanab             #+#    #+#             */
/*   Updated: 2022/07/18 21:40:35 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	atoi_check(char *number)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	sign = 1;
	if (*number == '\0')
		return (-1);
	if (number[i] == '-' || number[i] == '+')
	{
		if (number[i++] == '-')
			return (-1);
		if (number[i] < '0' || number[i] > '9')
			return (-1);
	}
	num = 0;
	while (number[i])
	{
		if (number[i] < '0' || number[i] > '9')
			return (-1);
		num = num * 10 + (number[i++] - '0');
	}
	if (sign * num <= INT_MIN || sign * num >= INT_MAX)
		return (-1);
	return (sign * num);
}

time_t	get_curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((time_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

time_t	meals_time_diff(t_data *data, int philo_i)
{
	time_t	last_meal_time;
	time_t	simulation_dur;

	last_meal_time = data->philos[philo_i].last_time_eaten - data->start_time;
	simulation_dur = get_curr_time() - data->start_time;
	return (last_meal_time + simulation_dur);
}

void	sleep_usec(time_t usec)
{
	time_t	start_time;

	start_time = get_curr_time();
	usleep(usec * 8 / 10);
	while (get_curr_time() - start_time < usec)
		usleep(500);
}

void	print_msg(int philo_id, int state, t_data data, bool unlock_mutex)
{
	time_t	timestamp;

	timestamp = get_curr_time() - data.start_time;
	pthread_mutex_lock(&(data.write_mutex));
	if (state == TAKEN_FORK)
		printf("%ld %d has taken a fork\n", timestamp, philo_id);
	else if (state == EATING)
		printf("%ld %d is eating\n", timestamp, philo_id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", timestamp, philo_id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", timestamp, philo_id);
	else if (state == DIED)
		printf("%ld %d died\n", timestamp, philo_id);
	else if (state == DONE)
		printf("%ld philosophers ate %d times\n", timestamp,
			data.n_times_to_eat);
	if (unlock_mutex)
		pthread_mutex_unlock(&(data.write_mutex));
}
