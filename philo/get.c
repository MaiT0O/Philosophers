#include "philo.h"

int	is_simulation_running(t_data *data)
{
    int	running;

    pthread_mutex_lock(&data->simulation_mutex);
    running = data->simulation_running;
    pthread_mutex_unlock(&data->simulation_mutex);
    return (running);
}

void	stop_simulation(t_data *data)
{
    pthread_mutex_lock(&data->simulation_mutex);
    data->simulation_running = 0;
    pthread_mutex_unlock(&data->simulation_mutex);
}

int	get_philo_full(t_data *data)
{
    int	full;

    pthread_mutex_lock(&data->philo_full_mutex);
    full = data->philo_full;
    pthread_mutex_unlock(&data->philo_full_mutex);
    return (full);
}

void	increment_philo_full(t_data *data)
{
    pthread_mutex_lock(&data->philo_full_mutex);
    data->philo_full++;
    pthread_mutex_unlock(&data->philo_full_mutex);
}

long	get_last_eat(t_philo *philo)
{
    long	last_eat;

    pthread_mutex_lock(&philo->last_eat_mutex);
    last_eat = philo->last_eat;
    pthread_mutex_unlock(&philo->last_eat_mutex);
    return (last_eat);
}

void	set_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->last_eat_mutex);
}
