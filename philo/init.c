#include "philo.h"

int	init_array_fork(t_data *data)
{
	int	i;

	i = 0;
	data->fork = (int *)malloc(sizeof(int) * data->philo_count);
	if (!data->fork)
	{
		printf("%s\n", ERR_MEMORY_ALLOC);
		return (0);
	}
	while (i < data->philo_count)
	{
		data->fork[i] = 1;
		i++;
	}
	return (1);
}

int	init_alone_philo(t_data *data)
{
	data_philo_init(data, 0);
	if (pthread_create(&data->philos[0].thread, NULL,
			alone_philosophe_routine, &data->philos[0]) != 0)
	{
		printf("%s %d.\n", ERR_THREAD, 1);
		return (0);
	}
	return (1);
}

void	*alone_philosophe_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[0]);
	print_fork(philo);
	philosopher_think(philo);
	philosopher_sleep(philo);
	while (philo->death == 0)
		usleep(1000);
	pthread_mutex_unlock(&philo->data->forks[0]);
	return (NULL);
}

int	create_monitor_thread(t_data *data)
{
	if (pthread_create(&data->monitor_thread, NULL,
			monitor_routine, data) != 0)
	{
		printf("Error: Failed to create monitor thread.\n");
		return (0);
	}
	return (1);
}
