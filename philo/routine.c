/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:56 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/29 16:30:28 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_think(t_philo *philo)
{
	if (is_running(philo->data))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", correct_time(philo->data),
			philo->id, MSG_THINKING);
		pthread_mutex_unlock(&philo->data->print);
	}
	return ;
}

void	philosopher_sleep(t_philo *philo)
{
	if (is_running(philo->data))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", correct_time(philo->data),
			philo->id, MSG_SLEEPING);
		pthread_mutex_unlock(&philo->data->print);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return ;
}

void	philosopher_eat(t_philo *philo)
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
	}
	return ;
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
		philosopher_think(philo);
		if (!is_running(philo->data))
			break ;
		take_forks(philo);
		if (!is_running(philo->data))
		{
			release_forks(philo);
			break ;
		}
		philosopher_eat(philo);
		release_forks(philo);
		if (!is_running(philo->data))
			break ;
		philosopher_sleep(philo);
	}
	return (NULL);
}
