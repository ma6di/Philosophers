#include "philosophers.h"

void write_status(t_status status, t_philos *philo)
{
    pthread_mutex_lock(&philo->data->write_mutex);
    long elapsed;

    elapsed = get_time(MILLISECOND) - philo->data->start_time;

    if (philo->full && status != DIED)
    {
        pthread_mutex_unlock(&philo->data->write_mutex);
        return;
    }
    if(status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
        printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
    else if (status == EATING && !(philo->data->end_time))
        printf(GREEN"%-6ld %d is eating\n"RESET, elapsed, philo->id);
    else if (status == SLEEPING && !(philo->data->end_time))
        printf("%-6ld %d is sleeping\n", elapsed, philo->id);
    else if (status == THINKING && !(philo->data->end_time))
        printf("%-6ld %d is thinking\n", elapsed, philo->id);
    else if (status == DIED)
        printf(RED"%-6ld %d died\n"RESET, elapsed, philo->id);

    pthread_mutex_unlock(&philo->data->write_mutex);
}