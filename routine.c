#include "philo.h"

long	get_time()
{
	struct timeval tv;
	long	res;

	if (gettimeofday(&tv, NULL) != 0)
    {
        printf("Error: Failed to get current time.\n");
        return (-1);
    }
    res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

void	*philo_routine(void *datas)
{
	pthread_t	tid;
	t_data		*data;

	data = (t_data *)datas;
	tid = pthread_self();
	
}