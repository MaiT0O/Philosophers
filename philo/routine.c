/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:56 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/28 16:29:08 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_think(t_philo *philo)
{
	if (is_running(philo->data))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", correct_time(philo->data),
			philo->id, MSG_THINKING);
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	return (0);
}

int	philosopher_sleep(t_philo *philo)
{
	if (is_running(philo->data))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", correct_time(philo->data),
			philo->id, MSG_SLEEPING);
		pthread_mutex_unlock(&philo->data->print);
		usleep(philo->data->time_to_sleep * 1000);
		return (1);
	}
	return (0);
}

int	philosopher_eat(t_philo *philo)
{
	if (is_running(philo->data))
	{
		philo->eat_count++;
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", correct_time(philo->data), philo->id, MSG_EATING);
		pthread_mutex_unlock(&philo->data->print);
		set_last_eat(philo);
		usleep(philo->data->time_to_eat * 1000);
		if (philo->eat_count == philo->data->must_eat_count)
			increment_philo_full(philo->data);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		if (!is_running(data))
			break ;
		i = 0;
		while (i < data->philo_count && is_running(data))
		{
			if (is_full(data) || is_dead(&data->philos[i]))
			{
				stop_simulation(&data->philos[i]);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (is_running(philo->data))
	{
		if (!philosopher_think(philo))
			break ;
		if (!take_forks(philo))
			break ;
		if (!philosopher_eat(philo))
		{
			release_forks(philo);
			break ;
		}
		release_forks(philo);
		if (!philosopher_sleep(philo))
			break ;
	}
	return (NULL);
}
