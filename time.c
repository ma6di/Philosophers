#include "philosophers.h"

long get_time(t_time_code time_code)
{

    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        ft_error("gettimeofday failed");

    long time_in_usec = (tv.tv_sec * 1000000) + tv.tv_usec;

    if (time_code == SECOND)
        return time_in_usec / 1000000;
    if (time_code == MILLISECOND)
        return time_in_usec / 1000;
    if (time_code == MICROSECOND)
        return time_in_usec;
    
    ft_error("wrong input to get_time");
    return -1; // Should never reach here due to the error call
}
void    percise_usleep(long usec, t_data *data) //try with usleep
{
    long    start;
    long    elapsed;
    long    rem;

    start = get_time(MICROSECOND);
    while (get_time(MICROSECOND) - start < usec )
    {
        if(data->end_time)
            break;
        elapsed = get_time(MICROSECOND) - start;
        rem = usec - elapsed;
        if(rem > 1e6)
            usleep(rem / 2);
        else
        {
            while (get_time(MICROSECOND) - start < usec )
                ;
        }
    }
}

/*void percise_usleep(long usec, t_data *data)
{

    long start_time, elapsed_time;

    start_time = get_time(MICROSECOND);
    while (1)
    {
        if (data->end_time)
            break;

        elapsed_time = get_time(MICROSECOND) - start_time;
        if (elapsed_time >= usec)
            break;

        // Sleep for a small fraction of the requested time to avoid busy-waiting
        usleep((usec - elapsed_time > 1000) ? (usec - elapsed_time) / 2 : (usec - elapsed_time));
    }
}*/
