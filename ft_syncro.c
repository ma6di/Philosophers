#include "philosophers.h"

void wait_all_threads(t_data *data)
{
    while (1)
    {
        if (pthread_mutex_lock(&data->data_mutex) != 0)
        {
            ft_error("Failed to lock data_mutex in wait_all_threads");
        }
        
        bool ready = data->all_threads_ready;
        
        if (pthread_mutex_unlock(&data->data_mutex) != 0)
        {
            ft_error("Failed to unlock data_mutex in wait_all_threads");
        }
        
        if (ready)
        {
            break;
        }
        usleep(1000);  // Sleep for 1 millisecond
    }
}

bool    all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
    bool ret;

    ret = false;
    pthread_mutex_lock(mutex);
    if (*threads == philo_nbr)
        ret = true;
    pthread_mutex_unlock(mutex);
    return ret;
}

void thread_ready(t_philos *philo)
{
    if (pthread_mutex_lock(&philo->data->data_mutex) != 0)
    {
        ft_error("Failed to lock data_mutex in thread_ready");
    }
    
    philo->data->threads_running_nbr3++;
    if (philo->data->threads_running_nbr3 == philo->data->philo_nbr)
    {
        philo->data->all_threads_ready = true;
    }
    
    if (pthread_mutex_unlock(&philo->data->data_mutex) != 0)
    {
        ft_error("Failed to unlock data_mutex in thread_ready");
    }
}

void    de_sync(t_philos *philo)
{
    if(philo->data->philo_nbr %2 == 0)
    {
        if(philo->id % 2 == 0)
            percise_usleep(3e4, philo->data);
    }
    else
    {
        if(philo->id % 2)
            thinking(philo, true);
    }
}
