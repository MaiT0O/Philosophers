#include "philo.h"

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
	pthread_mutex_unlock(philo->data->print);
}

int	safe_forks(t_philo *philo, int flag)
{
	if (!philo->data->simulation_running)
	{
		if (philo->id % 2 == 0 && flag == 0)
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		else if (philo->id % 2 == 0 && flag == 1)
			release_forks(philo);
		else if (philo->id % 2 != 0 && flag == 0)
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		else if (philo->id % 2 != 0 && flag == 1)
			release_forks(philo);
		printf("philo[%d] release fork\n", philo->id);
		return (0);
	}
	return (1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	take_forks(t_philo *philo)
{
	if (philo->data->simulation_running)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			if (!safe_forks(philo, 0))
				return ;
			print_fork(philo);
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			if (!safe_forks(philo, 1))
				return ;
			print_fork(philo);
		}
		else
		{
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			if (!safe_forks(philo, 0))
				return ;
			print_fork(philo);
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			if (!safe_forks(philo, 1))
				return ;
			print_fork(philo);
		}
	}
}

void	*alone_philosophe_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	pthread_mutex_lock(&philo->data->forks[0]);
	print_fork(philo);
	philosopher_think(philo);
	philosopher_sleep(philo);
	while (philo->death == 0)
		usleep(1000);
	print_death(philo);
	return (NULL);
}
