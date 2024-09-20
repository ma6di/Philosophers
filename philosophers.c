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
		ft_error("Memory allocation failed", data);
	if (argc == 5 || argc == 6)
	{
		input_pars(data, argv, argc);
		ft_mutex_init(data);
		ft_philo_init(data);
		dinner_start(data);
		clean(data);
	}
	else
		ft_error("Wrong number of arguments", data);
	free(data);
	return (0);
}
