#include "philosophers.h"

int main(int argc, char **argv)
{
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
    {
        ft_error("Memory allocation failed");
    }

    // Initialize data and handle errors
    if (argc == 5 || argc == 6)
    {
        input_pars(data, argv, argc);
        ft_mutex_init(data);
        ft_philo_init(data);
        dinner_start(data);
        clean(data);
    }
    else
    {
        free(data);
        ft_error("Wrong number of arguments");
    }

    free(data);
    return 0;
}