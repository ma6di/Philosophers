/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:04:07 by mcheragh          #+#    #+#             */
/*   Updated: 2024/09/20 12:05:15 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error2("Memory allocation failed", data);
	if (argc == 5 || argc == 6)
	{
		input_pars(data, argv, argc);
		ft_mutex_init(data);
		ft_philo_init(data);
		dinner_start(data);
		clean(data);
	}
	else
		ft_error2("Wrong number of arguments", data);
	return (0);
}

void	ft_error2(const char *error, t_data *data)
{
	if (error) 
	{
		write(2, RED"Error: ", 14);
		write(2, error, strlen(error));
		write(2, "\n"RESET, 5);
	}
	if (data)
		free(data);
	exit(EXIT_FAILURE);
}

void	ft_error1(const char *error, t_data *data)
{
	if (error) 
	{
		write(2, RED"Error: ", 14);
		write(2, error, strlen(error));
		write(2, "\n"RESET, 5);
	}
	if (data)
		clean(data);
	exit(EXIT_FAILURE);
}
