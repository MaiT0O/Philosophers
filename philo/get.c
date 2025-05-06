/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:36:54 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/30 13:36:23 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_running(t_data *data)
{
	bool	res;

	res = true;
	pthread_mutex_lock(&data->simulation_mutex);
	if (data->simulation_running == false)
		res = false;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (res);
}

void	stop_simulation(t_data *data, bool state)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_running = state;
	pthread_mutex_unlock(&data->simulation_mutex);
}

int	get_philo_full(t_data *data)
{
	int	full;

	pthread_mutex_lock(&data->philo_full_mutex);
	full = data->philo_full;
	pthread_mutex_unlock(&data->philo_full_mutex);
	return (full);
}

void	increment_philo_full(t_data *data)
{
	pthread_mutex_lock(&data->philo_full_mutex);
	data->philo_full++;
	pthread_mutex_unlock(&data->philo_full_mutex);
}

time_t	get_last_eat(t_philo *philo)
{
	long	last_eat;

	pthread_mutex_lock(&philo->last_eat_mutex);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (last_eat);
}
