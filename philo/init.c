/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:36:40 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/30 13:36:28 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*alone_philosophe_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_fork(philo);
	philosopher_think(philo);
	while (!is_dead(philo))
		usleep(1000);
	stop_simulation(philo);
	return (NULL);
}

int	init_list(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * (data->philo_count + 1));
	if (!data->philos)
	{
		printf("%s\n", ERR_MEMORY_ALLOC);
		return (0);
	}
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_count);
	if (!data->forks)
	{
		free(data->philos);
		printf("%s\n", ERR_MEMORY_ALLOC);
		return (0);
	}
	return (1);
}

void	set_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->last_eat_mutex);
}
