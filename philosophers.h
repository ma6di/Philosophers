/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:05:42 by mcheragh          #+#    #+#             */
/*   Updated: 2024/09/20 12:18:57 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

# define GREEN				"\033[0;32m"
# define RED				"\033[1;31m"
# define GREY				"\033[0;90m"
# define CYAN				"\033[1;96m"
# define RESET				"\033[0m"

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}	t_fork;

typedef struct s_philos
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_data				*data;
	pthread_mutex_t		philo_mutex;
}	t_philos;

struct s_data
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_limit;
	long				start_time;
	long				threads_running_nbr;
	bool				end_time;
	pthread_t			monitor;
	pthread_mutex_t		data_mutex;
	pthread_mutex_t		end_mutex;
	pthread_mutex_t		write_mutex;
	t_fork				*forks;
	t_philos			*philos;
};

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_status;

void	ft_error1(const char *error, t_data *data);
void	input_pars(t_data *data, char **argv, int argc);
void	ft_int_max(long num);
void	ft_mutex_init(t_data *data);
void	ft_philo_init(t_data *data);
void	ft_assign_fork(t_philos *philo, t_fork *forks, int position);
void	dinner_start(t_data *data);
void	*dinner_simulation(void *data);
long	get_time(t_time_code time_code, t_data *data);
void	percise_usleep(long usec, t_data *data);
void	write_status(t_status status, t_philos *philo);
void	input_parss(t_data *data, char **argv, int argc);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads, \
		long philo_nbr);
void	*monitor_dinner(void *data);
void	*one_philo(void *arg);
void	clean(t_data *data);
void	thinking(t_philos *philo, bool status);
bool	end_time(t_data *data, int flag);
void	more_than_one_philo(t_data *data);
void	set_start_time(t_philos *philo);
void	eat(t_philos *philo);
void	*monitor_dinner2(void *table);
bool	philo_died(t_philos *philo);
void	ft_error2(const char *error, t_data *data);

#endif
