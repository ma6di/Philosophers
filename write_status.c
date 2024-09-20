/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:44:59 by mcheragh          #+#    #+#             */
/*   Updated: 2024/09/20 12:46:34 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_status(t_status status, t_philos *philo)
{
	long	elapsed;

	pthread_mutex_lock(&philo->data->write_mutex);
	pthread_mutex_lock(&philo->data->data_mutex);
	elapsed = get_time(MILLISECOND, philo->data) - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (philo->full && status != DIED)
	{
		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !end_time(philo->data, 0))
		printf(GREEN"%-6ld %d is eating\n"RESET, elapsed, philo->id);
	else if (status == SLEEPING && !end_time(philo->data, 0))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !end_time(philo->data, 0))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf(RED"%-6ld %d died\n"RESET, elapsed, philo->id);
	pthread_mutex_unlock(&philo->data->write_mutex);
}
