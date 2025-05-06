/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:53 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/02 13:00:40 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].id = i;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_count;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = data->start;
		data->philos[i].data = data;
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
		|| pthread_mutex_init(&data->philo_full_mutex, NULL) != 0)
	{
		printf("%s\n", ERR_MUTEXES);
		return (0);
	}
	return (1);
}

bool	begin_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine
				, &data->philos[i]) != 0)
			return (printf("bp: error init thread"), free_all(data), false);
		i++;
	}
	if (data->philo_count > 1)
	{
		if (pthread_create(&data->monitor_thread, NULL, monitor_routine
				, data) != 0)
			return (printf("bp: error init threat"), free_all(data), false);
	}
	return (true);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("ITP: error malloc"), NULL);
	data->philo_count = ft_atoi_custom(argv[1]);
	data->time_to_die = ft_atoi_custom(argv[2]);
	data->time_to_eat = ft_atoi_custom(argv[3]);
	data->time_to_sleep = ft_atoi_custom(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi_custom(argv[5]);
	else
		data->must_eat_count = -1;
	data->philo_full = 0;
	data->simulation_running = true;
	data->start = get_time_ms() + (data->philo_count * 2 * 10);
	if (!init_list(data))
		return (NULL);
	if (!init_philosophers(data))
		return (NULL);
	if (!init_mutexes(data))
		return (NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (!validate_arguments(argc, argv))
		exit(1);
	data = init_data(argc, argv);
	if (!data)
		exit (1);
	if (!begin_process(data))
		exit (1);
	end(data);
	return (0);
}
