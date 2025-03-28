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

int initialize_data(t_data *data, int argc, char **argv)
{
    data->philo_count = ft_atoi_custom(argv[1]);
    data->time_to_die = ft_atoi_custom(argv[2]);
    data->time_to_eat = ft_atoi_custom(argv[3]);
    data->time_to_sleep = ft_atoi_custom(argv[4]);
    data->must_eat_count = (argc == 6) ? ft_atoi_custom(argv[5]) : -1;
    data->philo_full = 0;
    data->start = 0;
    data->forks = NULL;
    data->philos = NULL;

    if (data->philo_count <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
    {
        printf("Error: All arguments must be positive integers.\n");
        return (0);
    }
    return (1);
}

int	initialize_philosophers(t_data *data)
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
		data->philos[i].id = i;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_count;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = 0;
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

int	initialize_mutexes(t_data *data)
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
			printf("Error: Failed to initialize mutex.\n");
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

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return (1);
    }
    if (!validate_arguments(argc, argv))
        return (0);
    if (!initialize_data(&data, argc, argv))
        return (0);

    printf("Initialization successful!\n");
    printf("Philosophers: %d, Time to die: %dms, Time to eat: %dms, Time to sleep: %dms, Must eat: %d\n",
           data.philo_count, data.time_to_die, data.time_to_eat, data.time_to_sleep,
           (data.must_eat_count == -1) ? 0 : data.must_eat_count);

    // Vous pouvez maintenant continuer avec l'initialisation des philosophes et des mutex.
	// Vous pouvez également ajouter des fonctions pour libérer la mémoire et afficher des messages.
	if (!initialize_philosophers(&data))
		return (0);
	if (!initialize_mutexes(&data))
		return (0);

    return (0);
}
