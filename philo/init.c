/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:36:40 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/15 12:36:41 by ebansse          ###   ########.fr       */
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

void	*alone_philosophe_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[0]);
	print_fork(philo);
	philosopher_think(philo);
	philosopher_sleep(philo);
	while (is_running(philo->data))
		usleep(1000);
	philo->data->die = 1;
	pthread_mutex_unlock(&philo->data->forks[0]);
	stop_simulation(philo);
	end(philo->data);
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
