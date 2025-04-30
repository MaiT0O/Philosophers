/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:53 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/30 13:23:56 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_count = ft_atoi_custom(argv[1]);
	data->time_to_die = ft_atoi_custom(argv[2]);
	data->time_to_eat = ft_atoi_custom(argv[3]);
	data->time_to_sleep = ft_atoi_custom(argv[4]);
	data->die = 0;
	if (argc == 6)
		data->must_eat_count = ft_atoi_custom(argv[5]);
	else
		data->must_eat_count = INT_MIN;
	data->philo_full = 0;
	data->simulation_running = 1;
	data->forks = NULL;
	data->philos = NULL;
	data->start = get_time_ms();
	if (!init_list(data))
		return (0);
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (!data_philo_init(data, i))
			return (0);
	}
	return (1);
}

int	data_philo_init(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].left_fork = i;
	data->philos[i].right_fork = (i + 1) % data->philo_count;
	data->philos[i].eat_count = 0;
	data->philos[i].last_eat = get_time_ms();
	data->philos[i].data = data;
	if (data->philo_count == 1)
		return (1);
	else if (pthread_create(&data->philos[i].thread, NULL,
			philosopher_routine, &data->philos[i]) != 0)
	{
		printf("%s %d.\n", ERR_THREAD, i + 1);
		return (0);
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0
			|| pthread_mutex_init(&data->philos[i].last_eat_mutex, NULL) != 0)
		{
			printf("%s\n", ERR_MUTEXES);
			return (0);
		}
	}
	if (pthread_mutex_init(&data->print, NULL) != 0
		|| pthread_mutex_init(&data->simulation_mutex, NULL) != 0
		|| pthread_mutex_init(&data->philo_full_mutex, NULL) != 0
		|| pthread_mutex_init(&data->start_mutex, NULL) != 0)
	{
		printf("%s\n", ERR_MUTEXES);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("%s\n", USAGE);
		return (1);
	}
	if (!validate_arguments(argc, argv))
		return (1);
	if (!init_data(&data, argc, argv))
		return (free_all(&data));
	if (!init_mutexes(&data))
		return (free_all(&data));
	if (data.philo_count == 1)
	{
		if (!init_alone_philo(&data))
			return (end(&data));
		return (end(&data));
	}
	if (!init_philosophers(&data))
		return (end(&data));
	if (!create_monitor_thread(&data))
		return (end(&data));
	end(&data);
	return (0);
}
