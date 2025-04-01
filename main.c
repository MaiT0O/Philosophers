#include "philo.h"

int validate_arguments(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (ft_atoi_custom(argv[i]) <= 0)
        {
            printf("Error: Invalid argument '%s'. All values must be positive integers.\n", argv[i]);
            return (0);
        }
        i++;
    }
    return (1);
}

int init_data(t_data *data, int argc, char **argv)
{
	struct timeval tv;

    data->philo_count = ft_atoi_custom(argv[1]);
    data->time_to_die = ft_atoi_custom(argv[2]);
    data->time_to_eat = ft_atoi_custom(argv[3]);
    data->time_to_sleep = ft_atoi_custom(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi_custom(argv[5]);
	else
		data->must_eat_count = -1;
    data->philo_full = 0;
    data->start = 0;
	data->simulation_running = 1;
    data->forks = NULL;
    data->philos = NULL;

    if (data->philo_count <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
    {
        printf("Error: All arguments must be positive integers.\n");
        return (0);
    }
	if (gettimeofday(&tv, NULL) != 0)
    {
        printf("Error: Failed to get current time.\n");
        return (0);
    }
    data->start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (1);
}

int	init_philosophers(t_data *data)
{
	int i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
	{
		printf("Error: Failed to allocate memory for philosophers.\n");
		return (0);
	}
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_count;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = 0;
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	int i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
	{
		printf("Error: Failed to allocate memory for forks.\n");
		return (0);
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i]);
            free(data->forks);
            return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		printf("Error: Failed to initialize mutex.\n");
		return (0);
	}
	return (1);
}

int create_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_count)
    {
        if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine, &data->philos[i]) != 0)
        {
            printf("Error: Failed to create thread for philosopher %d.\n", i + 1);
            return (0);
        }
        i++;
    }
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data) != 0)
	{
		printf("Error: Failed to create monitor thread.\n");
		return (0);
	}
    return (1);
}

void join_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_count)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
    {
        printf("%s\n", USAGE);
        return (1);
    }
    if (!validate_arguments(argc, argv))
        return (1);
    if (!initialize_data(&data, argc, argv))
        return (1);
    if (!initialize_philosophers(&data))
        return (1);
    if (!initialize_mutexes(&data))
        return (1);
    if (!create_threads(&data))
        return (1);
    join_threads(&data);
    // Nettoyer les ressources
    int i = 0;
    while (i < data.philo_count)
        pthread_mutex_destroy(&data.forks[i++]);
    pthread_mutex_destroy(&data.print);
    free(data.forks);
    free(data.philos);

    return (0);
}
