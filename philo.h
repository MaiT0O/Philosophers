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
    int             death;
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
    int				simulation_running;
    pthread_mutex_t	*print;
    pthread_mutex_t	*forks;
	pthread_t		monitor_thread;
    t_philo			*philos;
}				t_data;

long	ft_atoi_custom(const char *str);
void *philosopher_routine(void *arg);
void *monitor_routine(void *arg);
int	free_all(t_data *data, int flag);
void end(t_data *data);
int validate_arguments(int argc, char **argv);
long	get_time_ms(void);
void take_forks(t_philo *philo);
void release_forks(t_philo *philo);
int is_dead(t_philo *philo);
void    print_death(t_philo *philo);

// Messages pour les philosophes
#define MSG_TAKE_FORK "has taken a fork"
#define MSG_EATING "is eating"
#define MSG_SLEEPING "is sleeping"
#define MSG_THINKING "is thinking"
#define MSG_DIED "died"

// Autres messages
#define ERR_INVALID_ARGS "Error: Invalid arguments. All values must be positive integers."
#define ERR_MEMORY_ALLOC "Error: Failed to allocate memory."
#define USAGE "Usage: ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
#define ERR_THREAD "Error: Failed to create thread for philosopher"

#endif