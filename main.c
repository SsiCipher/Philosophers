/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:07 by yanab             #+#    #+#             */
/*   Updated: 2022/05/23 15:40:42 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *error)
{
	if (!error)
		return (0);
	while (*error)
		write(2, error++, 1);
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_error("Error:\nWrong arguments\n"));
	if (!init_data(&data, argc - 1, argv + 1))
		return (print_error("Error:\nFailed to initialize data\n"));
	i = 0;
	while (i < data.philos_count)
	{
		pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < data.philos_count)
	{
		pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);
		i += 2;
	}
	while (1);
	return (0);
}
