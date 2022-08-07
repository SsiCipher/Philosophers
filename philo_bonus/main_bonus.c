/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:07 by yanab             #+#    #+#             */
/*   Updated: 2022/08/07 04:04:21 by yanab            ###   ########.fr       */
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
	int	i;

	i = -1;
	while (++i < data->philos_count)
		kill(data->philos[i].pid, SIGINT);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		status;

	if (argc != 5 && argc != 6)
		return (print_error("Error: Wrong arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!init_data(data, argc - 1, argv + 1))
		return (print_error("Error: Failed to initialize data\n"));
	data->start_time = get_curr_time();
	start_philos(data);
	while (waitpid(-1, &status, 0) != -1)
	{
		if (status > 0)
			kill_all(data);
	}
	return (0);
}
