#include "philo.h"

void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        // Philosophe pair : prend d'abord la fourchette gauche
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
        pthread_mutex_unlock(&philo->data->print);
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
        pthread_mutex_unlock(&philo->data->print);
    }
    else
    {
        // Philosophe impair : prend d'abord la fourchette droite
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
        pthread_mutex_unlock(&philo->data->print);
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
        pthread_mutex_unlock(&philo->data->print);
    }
}

void release_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        // Philosophe pair : libère d'abord la fourchette gauche
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
    }
    else
    {
        // Philosophe impair : libère d'abord la fourchette droite
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
    }
}

int	is_dead(t_philo *philo)
{
	long time_since_last_eat;

	if (philo->eat_count == 0)
		time_since_last_eat = get_time_ms() - philo->data->start;
	else if (philo->eat_count > 0)
		time_since_last_eat = get_time_ms() - philo->last_eat;
	if (time_since_last_eat > philo->data->time_to_die)
		return (1);
	return (0);
}

long	get_time_ms(void)
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
