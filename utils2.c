/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:06:09 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/08 16:43:03 by ebansse          ###   ########.fr       */
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
		return (1);
	}
	return (0);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("philophe[%d] hasn't eat since %ld ms\n", philo->id, philo->death_time);
	printf("%ld %d %s\n", get_time_ms(), philo->id, MSG_DIED);
	pthread_mutex_unlock(philo->data->print);
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

void	stop_sim(t_data *data, int flag)
{
	usleep(10000);
	data->simulation_running = 0;
	pthread_mutex_lock(data->print);
	if (flag == 1)
		printf("tous les philosophes ont manger a leur faim\n");
	pthread_mutex_unlock(data->print);
	return ;
}
