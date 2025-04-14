/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:56:17 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/14 15:52:14 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	philo->data->fork[philo->right_fork] = 1;
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	philo->data->fork[philo->left_fork] = 1;
}

void	print_think(t_philo *philo, int index)
{
	int	printed;

	printed = 0;
	if (philo->data->fork[index] == 1)
	{
		pthread_mutex_lock(&philo->data->forks[index]);
		philo->data->fork[index] = 0;
		return ;
	}
	while (philo->data->fork[index] == 0 && philo->data->simulation_running)
	{
		if (!printed)
		{
			pthread_mutex_lock(&philo->data->print);
			printf("%ld %d %s\n", correct_time(philo->data),
				philo->id, MSG_THINKING);
			pthread_mutex_unlock(&philo->data->print);
			printed = 1;
		}
		usleep(10000);
	}
}

int	safe_forks(t_philo *philo, int flag)
{
	if (!philo->data->simulation_running)
	{
		if (philo->id % 2 == 0 && flag == 0)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			philo->data->fork[philo->left_fork] = 1;
		}
		else if (philo->id % 2 != 0 && flag == 0)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			philo->data->fork[philo->right_fork] = 1;
		}
		else if (flag == 1)
			release_forks(philo);
		return (0);
	}
	return (1);
}

int	touch_fork(t_philo *philo, int left_fork, int right_fork)
{
	print_think(philo, left_fork);
	if (!safe_forks(philo, 0))
		return (0);
	print_fork(philo);
	print_think(philo, right_fork);
	if (!safe_forks(philo, 1))
		return (0);
	print_fork(philo);
	return (1);
}

void	take_forks(t_philo *philo)
{
	if (philo->data->simulation_running)
	{
		if (philo->id % 2 == 0)
		{
			touch_fork(philo, philo->left_fork, philo->right_fork);
		}
		else
		{
			touch_fork(philo, philo->right_fork, philo->left_fork);
		}
	}
}
