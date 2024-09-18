#include "philosophers.h"

// Handles the thinking state of a philosopher
void thinking(t_philos *philo, bool status)
{
    long t_eat;
    long t_sleep;
    long t_think;
    if(!status)
        write_status(THINKING, philo);
    if(philo->data->philo_nbr % 2 == 0)
        return;
    t_eat = philo->data->time_to_eat;
    t_sleep = philo->data->time_to_sleep;
    t_think = t_eat * 2 - t_sleep;
    if (t_think < 0)
        t_think = 0;
    percise_usleep(t_think * 0.42 ,philo->data);

}

void    *one_philo(void *arg)
{
    t_philos *philo;

    philo = (t_philos *)arg;
    wait_all_threads(philo->data);
    pthread_mutex_lock(&philo->philo_mutex);
    philo->last_meal_time = get_time(MILLISECOND);
    philo->data->threads_running_nbr++;
    pthread_mutex_unlock(&philo->data->data_mutex);
    write_status(TAKE_FIRST_FORK, philo);
    while(!philo->data->end_time)
        usleep(200);
    return (NULL);
}


static void eat(t_philos *philo)
{
    // Attempt to lock the first fork
    if (pthread_mutex_lock(&philo->first_fork->fork) != 0) 
    {
        ft_error("Failed to lock first fork");
    }
    write_status(TAKE_FIRST_FORK, philo); 
    // Attempt to lock the second fork
    if (pthread_mutex_lock(&philo->second_fork->fork) != 0) 
    {
        pthread_mutex_unlock(&philo->first_fork->fork);
        ft_error("Failed to lock second fork");
    }
    write_status(TAKE_SECOND_FORK, philo);

    // Update philosopher's last meal time
    pthread_mutex_lock(&philo->philo_mutex);
    philo->last_meal_time = get_time(MILLISECOND);
    philo->meals_counter++;
    pthread_mutex_unlock(&philo->philo_mutex);

    // Report the eating status
    write_status(EATING, philo);

    // Simulate the eating process
    percise_usleep(philo->data->time_to_eat, philo->data);

    // Update the full status if needed
    if (philo->data->meals_limit > 0 && philo->meals_counter == philo->data->meals_limit)
    {
        pthread_mutex_lock(&philo->philo_mutex);
        philo->full = true;
        pthread_mutex_unlock(&philo->philo_mutex);
    }

    if(pthread_mutex_unlock(&philo->first_fork->fork) != 0)
    {
        ft_error("failed to unlock first fork");
    }
    if(pthread_mutex_unlock(&philo->second_fork->fork) != 0)
    {
        ft_error("failed to unlock second fork");
    }
}

void dinner_start(t_data *data)
{
    int i;
    int result;

    if (data->meals_limit == 0)
        return;
    else if(data->philo_nbr == 1)
    {
        pthread_create(&data->philos[0].thread_id, NULL, one_philo, &data->philos[0]);
    }
    else
    {
        for(i = 0; i < data->philo_nbr; i++)
        {
            result = pthread_create(&data->philos[i].thread_id, NULL, dinner_simulation, &data->philos[i]);
            if (result != 0)
                ft_error("pthread_create failed");
        }

        pthread_create(&data->monitor, NULL, monitor_dinner, data );
        data->start_time = get_time(MILLISECOND);

        pthread_barrier_wait(&data->barrier2);

        for (i = 0; i < data->philo_nbr; i++)
        {
            result = pthread_join(data->philos[i].thread_id, NULL);
            if (result != 0)
                ft_error("pthread_join failed");
        }
        pthread_mutex_lock(&data->data_mutex);
        data->end_time = true;
        pthread_mutex_unlock(&data->data_mutex);
        pthread_join(data->monitor, NULL);
    }
}

void *dinner_simulation(void *data) 
{
    t_philos *philo = (t_philos *)data;

    printf("Thread %d started.\n", philo->id);

    thread_ready(philo);
    wait_all_threads(philo->data);

    //pthread_barrier_wait(&philo->data->barrier);

    if (pthread_mutex_lock(&philo->data->data_mutex) != 0)
    {
        ft_error("Failed to lock data_mutex for last meal time");
    }
    philo->last_meal_time = get_time(MILLISECOND);
    philo->data->threads_running_nbr++;
    if(pthread_mutex_unlock(&philo->data->data_mutex) != 0)
    {
        ft_error("Failed to unlock data_mutex for number of threads running");
    }

    while (!philo->data->end_time) 
    {
        if (philo->full) 
        {
            printf("Thread %d is full and exiting.\n", philo->id);
            break;
        }
        eat(philo);
        write_status(SLEEPING, philo);
        percise_usleep(philo->data->time_to_sleep, philo->data);
        thinking(philo, false );
    }
    printf("Thread %d finished dinner simulation.\n", philo->id);
    return NULL;
}
