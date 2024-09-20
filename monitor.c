/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:56:33 by mcheragh          #+#    #+#             */
/*   Updated: 2024/09/20 12:03:45 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	philo_died(t_philos *philo)
{
	long	elapsed;
	long	time_to_die;
	long	current_time;

	time_to_die = philo->data->time_to_die / 1e3;
	pthread_mutex_lock(&philo->philo_mutex);
	if (philo->full)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (false);
	}
	current_time = get_time(MILLISECOND, philo->data);
	elapsed = current_time - philo->last_meal_time;
	if (current_time == philo->data->start_time)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *table)
{
	int		i;
	t_data	*data;

	data = (t_data *) table;
	while (!all_threads_running(&data->data_mutex, &data->threads_running_nbr, \
				data->philo_nbr))
		;
	while (!end_time(data, 0))
	{
		i = 0;
		while (i < data->philo_nbr && !end_time(data, 0))
		{
			if (philo_died(data->philos + i))
			{
				end_time(data, 1);
				write_status(DIED, data->philos + i);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

bool	end_time(t_data *data, int flag)
{
	bool	status;

	pthread_mutex_lock(&data->end_mutex);
	status = data->end_time;
	if (flag == 1)
	{
		data->end_time = true;
	}
	pthread_mutex_unlock(&data->end_mutex);
	return (status);
}

void	clean(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->philos) 
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_destroy(&data->philos[i].philo_mutex);
			pthread_mutex_destroy(&data->forks[i].fork);
			i++;
		}
		free(data->forks);
		free(data->philos);
	}
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->end_mutex);
}
