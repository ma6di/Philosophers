#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>


# define GREEN				"\033[0;32m"
# define RED				"\033[1;31m"
# define GREY				"\033[0;90m"
# define CYAN				"\033[1;96m"
# define RESET				"\033[0m"

typedef struct s_data   t_data;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int             fork_id;
}   t_fork;

typedef struct s_philos
{
    int         id;
    long        meals_counter;
    bool        full;
    long        last_meal_time;
    t_fork      *first_fork;
    t_fork      *second_fork;
    pthread_t   thread_id;
    t_data      *data;
    pthread_mutex_t philo_mutex;
}   t_philos;

struct s_data
{
    long        philo_nbr;
    long        time_to_die;
    long        time_to_eat;
    long        time_to_sleep;
    long        meals_limit;
    long        start_time;
    long        threads_running_nbr;
    long        threads_running_nbr2;
    long        threads_running_nbr3;
    pthread_barrier_t barrier;
    pthread_barrier_t barrier2;
    bool        end_time;
    bool        all_threads_ready;
    pthread_t   monitor;
    pthread_mutex_t data_mutex;
    pthread_mutex_t write_mutex;
    t_fork      *forks;
    t_philos    *philos;
};

typedef enum e_time_code
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}   t_time_code;

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DIED,
}   t_status;

void    ft_error(const char *error);
void    input_pars(t_data *data, char **argv, int argc);
long    ft_atol(const char *str);
void    ft_int_max(long num);
void    ft_mutex_init(t_data *data);
void    ft_philo_init(t_data *data);
void    ft_assign_fork(t_philos *philo, t_fork *forks, int position);
void    wait_all_threads(t_data *data);
void    dinner_start(t_data *data);
void    *dinner_simulation(void *data);
long    get_time(t_time_code time_code);
void    percise_usleep(long usec, t_data *data);
void    write_status(t_status status, t_philos *philo);
void input_parss(t_data *data, char **argv, int argc);
bool    all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void    *monitor_dinner(void *data);
void    *one_philo(void *arg);
void thread_ready(t_philos *philo);
void    clean(t_data *data);
void thinking(t_philos *philo, bool status);






 
#endif
