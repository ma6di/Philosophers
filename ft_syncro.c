#include "philosophers.h"

bool all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
    bool ret;

    ret = false;
    pthread_mutex_lock(mutex);
    if (*threads == philo_nbr) 
    {
        ret = true;
        *threads = 0;
    } else 
        (*threads)++;
    pthread_mutex_unlock(mutex);
    return (ret);
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

void thinking(t_philos *philo, bool status)
{
    long t_eat;
    long t_sleep;
    long t_think;

    if(!status)
        write_status(THINKING, philo);
    if(philo->data->philo_nbr % 2 == 0)
        return ;
    t_eat = philo->data->time_to_eat;
    t_sleep = philo->data->time_to_sleep;
    t_think = t_eat * 2 - t_sleep;
    if (t_think < 0)
        t_think = 0;
    percise_usleep(t_think * 0.42, philo->data);
}
