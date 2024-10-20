/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:39:56 by mcheragh          #+#    #+#             */
/*   Updated: 2024/09/20 12:44:48 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(t_time_code time_code, t_data *data)
{
	struct timeval	tv;
	long			time_in_usec;

	if (gettimeofday(&tv, NULL))
		ft_error1("gettimeofday failed", data);
	time_in_usec = (tv.tv_sec * 1000000) + tv.tv_usec;
	if (time_code == SECOND)
		return (time_in_usec / 1000000);
	if (time_code == MILLISECOND)
		return (time_in_usec / 1000);
	if (time_code == MICROSECOND)
		return (time_in_usec);
	ft_error1("wrong input to get_time", data);
	return (-1); 
}

void	percise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND, data);
	while (get_time(MICROSECOND, data) - start < usec)
	{
		if (end_time(data, 0))
			break ;
		elapsed = get_time(MICROSECOND, data) - start;
		rem = usec - elapsed;
		if (rem > 1e6)
			usleep(rem / 2);
		else
		{
			while (get_time(MICROSECOND, data) - start < usec)
				;
		}
	}
}

void	set_start_time(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->data->start_time = get_time(MILLISECOND, philo->data);
	pthread_mutex_unlock(&philo->data->data_mutex);
}
