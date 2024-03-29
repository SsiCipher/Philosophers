/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 06:29:48 by yanab             #+#    #+#             */
/*   Updated: 2022/08/15 03:30:08 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	atoi_check(char *number)
{
	int			i;
	long long	num;

	i = 0;
	if (*number == '\0')
		return (-1);
	if (number[i] == '-' || number[i] == '+')
	{
		if (number[i++] == '-')
			return (-1);
	}
	num = 0;
	while (number[i])
	{
		if (number[i] < '0' || number[i] > '9')
			return (-1);
		num = num * 10 + (number[i++] - '0');
	}
	if (num >= INT_MAX)
		return (-1);
	return (num);
}

time_t	get_curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((time_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	sleep_usec(time_t usec)
{
	time_t	start_time;

	start_time = get_curr_time();
	usleep(usec * 8 / 10);
	while (get_curr_time() - start_time < usec)
		usleep(500);
}

time_t	calc_time_elapsed(t_data *data, int i)
{
	time_t	time_elapsed;

	if (data->philos[i].last_time_eaten == 0)
		time_elapsed = get_curr_time() - data->start_time;
	else
		time_elapsed = get_curr_time() - data->philos[i].last_time_eaten;
	return (time_elapsed);
}

void	print_msg(int philo_id, int state, t_data data, bool unlock_sem)
{
	time_t	timestamp;

	timestamp = get_curr_time() - data.start_time;
	sem_wait(data.write_sem);
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
	if (unlock_sem)
		sem_post(data.write_sem);
}
