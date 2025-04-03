/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:53 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/02 15:09:49 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		data->must_eat_count = INT_MIN;
    data->philo_full = 0;
	data->simulation_running = 1;
    data->forks = NULL;
    data->philos = NULL;
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
		printf("%s for philosophers.\n", ERR_MEMORY_ALLOC);
		return (0);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_count;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = 0;
		data->philos[i].data = data;
        if (pthread_create(&data->philos[i].thread, NULL,
			philosopher_routine, &data->philos[i]) != 0)
        {
            printf("%s %d.\n", ERR_THREAD, i + 1);
            return (0);
        }
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	int i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		 * data->philo_count);
	if (!data->forks)
	{
		printf("%s for forks.\n", ERR_MEMORY_ALLOC);
		return (0);
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			free_all(data, 1);
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

int create_monitor_thread(t_data *data)
{
	if (pthread_create(&data->monitor_thread, NULL,
		 monitor_routine, data) != 0)
	{
		printf("Error: Failed to create monitor thread.\n");
		return (0);
	}
    return (1);
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
        return (0);
	if (!init_data(&data, argc, argv))
        return (0);
	if (!init_mutexes(&data))
        return (free_all(&data, 1));
	if (!init_philosophers(&data))
        return (free_all(&data, 0));
	if (!create_monitor_thread(&data))
	{
		join_threads(&data);
		free_all(&data, 0);
		return (0);
	}
	join_threads(&data);
	free_all(&data, 0);
    return (1);
}
