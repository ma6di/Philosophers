#include "philosophers.h"

void ft_mutex_init(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
    if (!data->forks)
        ft_error("Memory allocation failed for forks");

    for (i = 0; i < data->philo_nbr; i++)
    {
        if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
        {
            ft_error("Mutex initialization failed for fork");
        }
        data->forks[i].fork_id = i;
    }

    if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
    {
        ft_error("Mutex initialization failed for data_mutex");
    }
    if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
    {
        ft_error("Mutex initialization failed for write_mutex");
    }
}


void ft_philo_init(t_data *data)
{
    int i;
    t_philos *philo;

    // Allocate memory for the philosophers array
    data->philos = malloc(sizeof(t_philos) * data->philo_nbr);
    if (!data->philos)
        ft_error("Memory allocation failed for philosophers");

    data->end_time = false;
    data->all_threads_ready = false; 
    data->threads_running_nbr = 0;
    data->threads_running_nbr2 = 0;
    data->threads_running_nbr3 = 0;

    // Initialize each philosopher
    for (i = 0; i < data->philo_nbr; i++)
    {
        philo = &data->philos[i]; // Access the philosopher

        philo->id = i + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->data = data;

        // Assign forks to the philosopher
        ft_assign_fork(philo, data->forks, i);

        // Initialize mutex for the philosopher
        if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
        {
            ft_error("Mutex initialization failed for philosopher's mutex");
        }
    }
    pthread_barrier_init(&data->barrier, NULL, data->philo_nbr);
    pthread_barrier_init(&data->barrier2, NULL, data->philo_nbr);


}

// Assigns forks to the philosopher based on their position
void ft_assign_fork(t_philos *philo, t_fork *forks, int position)
{
    int philo_nbr;

    philo_nbr = philo->data->philo_nbr; 

    // Assign the first and second fork
    philo->first_fork = &forks[(position + 1) % philo_nbr];
    philo->second_fork = &forks[position];

    // Swap the forks for even-indexed philosophers to avoid deadlock
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[position];
        philo->second_fork = &forks[(position + 1) % philo_nbr];
    }
}