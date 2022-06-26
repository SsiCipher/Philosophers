/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:07 by yanab             #+#    #+#             */
/*   Updated: 2022/06/26 05:48:39 by yanab            ###   ########.fr       */
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

void	start_philos(t_data *data)
{
	(void)data;
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (argc < 5 || argc > 6)
		return (print_error("Error:\nWrong arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!init_data(data, argc - 1, argv + 1))
		return (print_error("Error:\nFailed to initialize data\n"));
	start_philos(data);
	return (0);
}
