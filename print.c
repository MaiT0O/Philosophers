/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:44:21 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/11 15:57:15 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("%ld %d %s\n",correct_time(philo->data), philo->id, MSG_TAKE_FORK);
	pthread_mutex_unlock(philo->data->print);
}

void	print_think(t_philo *philo, int index)
{
	int	printed;

	printed = 0;
	while (pthread_mutex_lock(&philo->data->forks[index]) != 0 && philo->data->simulation_running)
	{
		if (!printed)
		{
			pthread_mutex_lock(philo->data->print);
			printf("%ld %d %s\n", correct_time(philo->data), philo->id, MSG_THINKING);
			pthread_mutex_unlock(philo->data->print);
			printed = 1;
		}
		usleep(10000);
	}
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("%ld philophe[%d] hasn't eat since %ld ms\n", correct_time(philo->data), philo->id, philo->death_time);
	printf("%ld %d %s\n", correct_time(philo->data), philo->id, MSG_DIED);
	pthread_mutex_unlock(philo->data->print);
}

void	print_meal(t_data *data)
{
    pthread_mutex_lock(data->print);
    printf("all philosophers have had enough to eat\n");
    pthread_mutex_unlock(data->print);
}