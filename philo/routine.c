/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:56 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/15 12:55:51 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_think(t_philo *philo)
{
	long	time_to_think;

	if (philo->data->simulation_running && !philo->death)
	{
		time_to_think = (philo->data->time_to_die - (get_time_ms()
					- philo->last_eat) - philo->data->time_to_eat
				- philo->data->time_to_sleep) / 2;
		if (time_to_think < 0)
			time_to_think = 0;
		if (time_to_think == 0)
			time_to_think = 1;
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", correct_time(philo->data),
			philo->id, MSG_THINKING);
		pthread_mutex_unlock(&philo->data->print);
		usleep(time_to_think * 1000);
	}
	return ;
}

void	philosopher_sleep(t_philo *philo)
{
	if (philo->data->simulation_running && !philo->death)
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
	if (philo->data->simulation_running && !philo->death)
	{
		philo->eat_count++;
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", correct_time(philo->data), philo->id, MSG_EATING);
		pthread_mutex_unlock(&philo->data->print);
		philo->last_eat = get_time_ms();
		usleep(philo->data->time_to_eat * 1000);
		if (philo->eat_count == philo->data->must_eat_count)
			philo->data->philo_full++;
	}
	return ;
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->simulation_running)
	{
		i = 0;
		while (i < data->philo_count && data->simulation_running)
		{
			if (is_full(data) || is_dead(&data->philos[i]))
				return (NULL);
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
	while (philo->data->simulation_running && !philo->death)
	{
		if (!philo->data->simulation_running || philo->death)
			break ;
		take_forks(philo);
		if (!philo->data->simulation_running || philo->death)
		{
			release_forks(philo);
			break ;
		}
		philosopher_eat(philo);
		release_forks(philo);
		if (!philo->data->simulation_running || philo->death)
			break ;
		philosopher_think(philo);
		if (!philo->data->simulation_running || philo->death)
			break ;
		philosopher_sleep(philo);
	}
	return (NULL);
}
