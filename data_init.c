/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:44:44 by mcheragh          #+#    #+#             */
/*   Updated: 2024/09/20 11:49:42 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_mutex_init(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		ft_error("Memory allocation failed for forks", data);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
			ft_error("Mutex initialization failed for fork", data);
		data->forks[i].fork_id = i;
		i++;
	}
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		ft_error("Mutex initialization failed for data_mutex", data);
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		ft_error("Mutex initialization failed for write_mutex", data);
	pthread_mutex_init(&data->end_mutex, NULL);
}

void	ft_philo_init(t_data *data)
{
	int			i;
	t_philos	*philo;

	data->philos = malloc(sizeof(t_philos) * data->philo_nbr);
	if (!data->philos)
		ft_error("Memory allocation failed for philosophers", data);
	data->end_time = false;
	data->threads_running_nbr = 0;
	i = 0;
	while (i < data->philo_nbr)
	{
		philo = &data->philos[i]; 
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->data = data;
		philo->last_meal_time = get_time(MILLISECOND, data); 
		ft_assign_fork(philo, data->forks, i);
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
			ft_error("Mutex initialization failed - philos mutex", data);
		i++;
	}
}

void	ft_assign_fork(t_philos *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr; 
	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
}
