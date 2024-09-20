/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:19:13 by mcheragh          #+#    #+#             */
/*   Updated: 2024/09/20 12:23:35 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(const char *error, t_data *data)
{
	if (error) 
	{
		write(2, RED"Error: ", 14);
		write(2, error, strlen(error));
		write(2, "\n"RESET, 5);
	}
	if (data)
	{
		clean(data);
		free(data);
	}
	exit(EXIT_FAILURE);
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r');
}

static long	ft_atol(const char *str, t_data *data)
{
	long	num;
	int		i;
	int		digit;

	num = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-') 
		ft_error("Negative input", data);
	while (str[i] != '\0') 
	{
		if (!ft_isdigit(str[i])) 
			ft_error("Non-numeric character found", data);
		digit = str[i] - '0';
		if (num > (LONG_MAX - digit) / 10)
			ft_error("Input exceeds LONG_MAX", data);
		num = num * 10 + digit;
		i++;
	}
	return (num);
}

void	input_pars(t_data *data, char **argv, int argc)
{
	if (argc != 5 && argc != 6)
		ft_error("wrong number of arguments", data);
	data->philo_nbr = ft_atol(argv[1], data);
	data->time_to_die = ft_atol(argv[2], data) * 1000;
	data->time_to_eat = ft_atol(argv[3], data) * 1000;
	data->time_to_sleep = ft_atol(argv[4], data) * 1000;
	if (argc == 6)
		data->meals_limit = ft_atol(argv[5], data);
	else
		data->meals_limit = -1;
	if (data->philo_nbr <= 0 || data->time_to_die < 60000 || \
			data->time_to_sleep < 60000 || data->time_to_eat < 60000)
		ft_error("Invalid input", data);
}
