/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:07 by yanab             #+#    #+#             */
/*   Updated: 2022/07/02 22:00:33 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	print_error(char *error)
{
	if (!error)
		return (false);
	while (*error)
		write(2, error++, 1);
	return (true);
}

void	kill_all(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philos_count)
		kill(data->philos[i].pid, SIGKILL);
	exit(EXIT_FAILURE);
}

void	start_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			kill_all(data);
		else if (data->philos[i].pid == 0)
			philo_routine(&(data->philos[i]));
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		wstatus;

	if (argc < 5 || argc > 6)
		return (print_error("Error:\nWrong arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!init_data(data, argc - 1, argv + 1))
		return (print_error("Error:\nFailed to initialize data\n"));
	start_philos(data);
	while (waitpid(-1, &wstatus, 0) != -1)
	{
		if (wstatus > 0)
			kill_all(data);
	}
	// sem_close(data->forks);
	// sem_close(data->death_sem);
	// sem_close(data->write_sem);
	return (0);
}
