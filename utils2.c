/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:06:09 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/11 17:14:50 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;

	current_time = get_time_ms();
	time_since_last_meal = current_time - philo->last_eat;
	if (time_since_last_meal > philo->data->time_to_die)
	{
		philo->death = 1;
		philo->death_time = time_since_last_meal;
		usleep(10000);
		philo->data->simulation_running = 0;
		print_death(philo);
		return (1);
	}
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

long	correct_time(t_data *data)
{
	long	time;

	time = get_time_ms();
	time = time - data->start;
	return (time);
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
