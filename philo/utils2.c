/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:06:09 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/15 12:46:39 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(t_data *data)
{
	if (get_philo_full(data) == data->philo_count)
		return (1);
	return (0);
}

int	is_dead(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;

	current_time = get_time_ms();
	time_since_last_meal = current_time - get_last_eat(philo);
	if (time_since_last_meal > philo->data->time_to_die)
	{
		philo->data->die = 1;
		return (1);
	}
	return (0);
}

long	get_time_ms(void)
{
	struct timeval	tv;
	long			res;

	if (gettimeofday(&tv, NULL) != 0)
	{
		printf("Error: Failed to get current time.\n");
		return (-1);
	}
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

long correct_time(t_data *data)
{
    long time;

    pthread_mutex_lock(&data->start_mutex);
    time = get_time_ms();
    time = time - data->start;
    pthread_mutex_unlock(&data->start_mutex);

    return (time);
}
