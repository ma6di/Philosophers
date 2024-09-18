#include "philosophers.h"

static bool philo_died(t_philos *philo)
{
    long elapsed;
    long time_to_die;
    time_to_die = philo->data->time_to_die / 1e3;
    pthread_mutex_lock(&philo->philo_mutex);
    if (philo->full)
    {
        pthread_mutex_unlock(&philo->philo_mutex);
        return (false);
    }
    elapsed = get_time(MILLISECOND) - philo->last_meal_time;
    pthread_mutex_unlock(&philo->philo_mutex);

    if(elapsed > time_to_die)
        return (true);
    return(false);
}

void    *monitor_dinner(void *table)
{
    int i;
    t_data *data;

    data = (t_data *) table;
    while(!all_threads_running(&data->data_mutex, &data->threads_running_nbr, data->philo_nbr))
        ;
    while(!data->end_time)
    {
        i = 0;
        while (i < data->philo_nbr && !data->end_time)
        {
            if(philo_died(data->philos + i))
            {
                data->end_time = true;
                write_status(DIED, data->philos + i);
            }
            i++;
        }
    }
    return (NULL);
}