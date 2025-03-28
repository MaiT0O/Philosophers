#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_philo
{
    int				id;
    int				left_fork;
    int				right_fork;
    int				eat_count;
    long			last_eat;
    pthread_t		thread;
    struct s_data	*data;
}				t_philo;

typedef struct s_data
{
    int				philo_count;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				must_eat_count;
    int				philo_full;
    long			start;
    pthread_mutex_t	*forks;
    pthread_mutex_t	print;
    t_philo			*philos;
}				t_data;

long	ft_atoi_custom(const char *str);

#endif