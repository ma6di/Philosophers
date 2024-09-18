#include "philosophers.h"

void ft_error(const char *error)
{
    printf("Error: %s\n", error);
    exit(EXIT_FAILURE);
}

long ft_atol(const char *str)
{
    long num = 0;
    int i = 0;

    //printf("Processing string: '%s'\n", str);

    // Skip leading whitespace
    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
        i++;

    // Check for sign
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
    {
        ft_error("negative input");
    }

    // Convert digits to number
    while (str[i] >= '0' && str[i] <= '9')
    {
        if (num > (LONG_MAX - (str[i] - '0')) / 10)
            ft_error("input bigger than LONG_MAX");
        num = num * 10 + (str[i] - '0');
        i++;
    }
    // Check for non-numeric characters after the digits
    if (str[i] != '\0')
       ft_error("non numeric character found");
    //printf("num is: '%ld'\n", num);
    return num;
}


void input_pars(t_data *data, char **argv, int argc)
{
    if (argc != 5 && argc != 6)
        ft_error("wrong number of arguments");

    data->philo_nbr = ft_atol(argv[1]);
    //printf("philo_nbr is: '%ld'\n", data->philo_nbr);
    data->time_to_die = ft_atol(argv[2]) * 1000;
    //printf("time_to_die is: '%ld'\n", data->time_to_die);
    data->time_to_eat = ft_atol(argv[3]) * 1000;
    //printf("time_to_eat is: '%ld'\n", data->time_to_eat);
    data->time_to_sleep = ft_atol(argv[4]) * 1000;
    //printf("time_to_sleep is: '%ld'\n", data->time_to_sleep);
    if (argc == 6)
    {
        data->meals_limit = ft_atol(argv[5]);
        //printf("meals_limit is: '%ld'\n", data->meals_limit);
    }
    else
    {
        data->meals_limit = -1;
        //printf("meals_limit is: '%ld'\n", data->meals_limit);
    }
    if (data->philo_nbr <= 0 || data->time_to_die < 60000 || data->time_to_sleep < 60000 || data->time_to_eat < 60000)
        ft_error("Invalid input: ensure numbers are positive and times are greater than 60ms");
    //printf("iam at end of input pars\n");
}

void    clean(t_data *data)
{
        for (int i = 0; i < data->philo_nbr; i++)
        {
            pthread_mutex_destroy(&data->forks[i].fork);
            pthread_mutex_destroy(&data->philos[i].philo_mutex);
        }
        pthread_mutex_destroy(&data->data_mutex);
        pthread_mutex_destroy(&data->write_mutex);
        pthread_barrier_destroy(&data->barrier);
        free(data->forks);
        free(data->philos);

}

