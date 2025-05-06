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

void	think_eat_sleep_process(t_philo *philo)
{
	print_statement(philo, "Think");
	take_forks(philo);
	print_statement(philo, "Eating");
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (philo->eat_count == philo->data->must_eat_count)
		increment_philo_full(philo->data);
	set_phi_to("Eat", philo);
	release_forks(philo);
	print_statement(philo, "Sleeping");
	set_phi_to("Sleep", philo);
}

void	*wait_till_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[0]);
	print_statement(philo, "Think");
	print_statement(philo, "Fork_0");
	set_phi_to("Die", philo);
	print_statement(philo, "Died");
	pthread_mutex_unlock(&philo->data->forks[0]);
	return (NULL);
}

bool	are_all_conditions_reached(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (is_dead(&data->philos[i]))
			return (true);
		i++;
	}
	if (get_philo_full(data) == data->philo_count)
	{
		stop_simulation(data, false);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sync_threads(data->start);
	while (true)
	{
		if (are_all_conditions_reached(data) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sync_threads(philo->data->start);
	if (philo->data->philo_count == 1)
		return (wait_till_die(philo), NULL);
	while (is_running(philo->data) == true)
		think_eat_sleep_process(philo);
	return (NULL);
}
