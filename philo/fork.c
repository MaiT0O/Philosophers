/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:56:17 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/15 12:40:32 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

int	safe_forks(t_philo *philo, int flag)
{
	if (!is_running(philo->data))
	{
		if (philo->id % 2 == 0 && flag == 0)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		}
		else if (philo->id % 2 != 0 && flag == 0)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		}
		else if (flag == 1)
			release_forks(philo);
		return (0);
	}
	return (1);
}

int	touch_fork(t_philo *philo, int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	if (!safe_forks(philo, 0))
		return (0);
	print_fork(philo);
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	if (!safe_forks(philo, 1))
		return (0);
	print_fork(philo);
	return (1);
}

void	take_forks(t_philo *philo)
{
	if (is_running(philo->data))
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
