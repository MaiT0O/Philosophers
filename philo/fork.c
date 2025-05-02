/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:56:17 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/02 13:14:46 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

int	touch_fork(t_philo *philo, int fork_1, int fork_2)
{
	pthread_mutex_lock(&philo->data->forks[fork_1]);
	if (!is_running(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[fork_1]);
		return (0);
	}
	print_fork(philo);
	pthread_mutex_lock(&philo->data->forks[fork_2]);
	if (!is_running(philo->data))
	{
		release_forks(philo);
		return (0);
	}
	print_fork(philo);
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (is_running(philo->data))
	{
		if (philo->id % 2 == 0)
		{
			if (!touch_fork(philo, philo->left_fork, philo->right_fork))
				return (0);
		}
		else
		{
			if (!touch_fork(philo, philo->right_fork, philo->left_fork))
				return (0);
		}
	}
	return (1);
}
