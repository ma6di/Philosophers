/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:27:08 by mcheragh          #+#    #+#             */
/*   Updated: 2024/09/20 12:39:39 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	set_start_time(philo);
	if (pthread_mutex_lock(&philo->first_fork->fork) != 0)
		ft_error1("Lone philo failed to lock first fork", philo->data);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal_time = get_time(MILLISECOND, philo->data);
	pthread_mutex_unlock(&philo->data->data_mutex);
	while (!end_time(philo->data, 0))
	{
		if (philo_died(philo)) 
		{
			end_time(philo->data, 1);
			write_status(DIED, philo);
			break ;
		}
		usleep(1000);
	}
	if (pthread_mutex_unlock(&philo->first_fork->fork) != 0)
		ft_error1("Lone philo failed to unlock first fork", philo->data);
	return (NULL);
}

void	eat(t_philos *philo)
{
	if (pthread_mutex_lock(&philo->first_fork->fork) != 0) 
		ft_error1("Failed to lock first fork", philo->data);
	write_status(TAKE_FIRST_FORK, philo); 
	if (pthread_mutex_lock(&philo->second_fork->fork) != 0) 
		ft_error1("Failed to lock second fork", philo->data);
	write_status(TAKE_SECOND_FORK, philo);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_time(MILLISECOND, philo->data);
	philo->meals_counter++;
	write_status(EATING, philo);
	pthread_mutex_unlock(&philo->philo_mutex);
	percise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->meals_limit > 0 && philo->meals_counter == \
			philo->data->meals_limit)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		philo->full = true;
		pthread_mutex_unlock(&philo->philo_mutex);
	}
	if (pthread_mutex_unlock(&philo->first_fork->fork) != 0)
		ft_error1("failed to unlock first fork", philo->data);
	if (pthread_mutex_unlock(&philo->second_fork->fork) != 0)
		ft_error1("failed to unlock second fork", philo->data);
}

void	dinner_start(t_data *data)
{
	if (data->meals_limit == 0)
		return ;
	if (data->philo_nbr == 1)
	{
		if (pthread_create(&data->philos[0].thread_id, NULL, \
					one_philo, &data->philos[0]) != 0)
			perror("Failed to create one_philo thread");
		if (pthread_join(data->philos[0].thread_id, NULL) != 0)
			perror("Failed to join one_philo thread");
	}
	else
		more_than_one_philo(data);
}

void	*dinner_simulation(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	all_threads_running(&philo->data->data_mutex, \
			&philo->data->threads_running_nbr, philo->data->philo_nbr);
	set_start_time(philo);
	if (pthread_mutex_lock(&philo->data->data_mutex) != 0)
		ft_error1("Failed to lock data_mutex", data);
	philo->last_meal_time = get_time(MILLISECOND, data);
	if (pthread_mutex_unlock(&philo->data->data_mutex) != 0)
		ft_error1("Failed to unlock data_mutex", data);
	while (!end_time(philo->data, 0)) 
	{
		if (philo->full) 
		{
			printf("Philo %d is full.\n", philo->id);
			break ;
		}
		eat(philo);
		write_status(SLEEPING, philo);
		percise_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo, false);
	}
	return (NULL);
}

void	more_than_one_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr) 
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, \
					dinner_simulation, &data->philos[i]))
			ft_error1("pthread_create failed", data);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_dinner, data);
	all_threads_running(&data->data_mutex, &data->threads_running_nbr, \
			data->philo_nbr);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			ft_error1("pthread_join failed for philosopher", data);
		i++;
	}
	end_time(data, 1);
	if (pthread_join(data->monitor, NULL) != 0)
		ft_error1("pthread_join failed for monitor", data);
}
