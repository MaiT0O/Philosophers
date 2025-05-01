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

int is_fork_locked(t_data *data, int fork_index)
{
    int locked;

    pthread_mutex_lock(&data->locked);
    locked = data->forks_locked[fork_index];
    pthread_mutex_unlock(&data->locked);

    return locked;
}

void set_fork_locked(t_data *data, int fork_index, int value)
{
    pthread_mutex_lock(&data->locked);
    data->forks_locked[fork_index] = value;
    pthread_mutex_unlock(&data->locked);
}

void release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
    if (is_fork_locked(philo->data, philo->right_fork))
    {
        printf("Unlocking right fork %d\n", philo->right_fork);
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		set_fork_locked(philo->data, philo->right_fork, 0);
    }
    if (is_fork_locked(philo->data, philo->left_fork))
    {
        printf("Unlocking left fork %d\n", philo->left_fork);
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		set_fork_locked(philo->data, philo->left_fork, 0);
    }
	pthread_mutex_unlock(&philo->data->print);
}

int	safe_forks(t_philo *philo)
{
	if (!is_running(philo->data))
	{
		release_forks(philo);
		return (0);
	}
	return (1);
}

int touch_fork(t_philo *philo, int left_fork, int right_fork)
{
    pthread_mutex_lock(&philo->data->forks[left_fork]);
    set_fork_locked(philo->data, left_fork, 1);
    if (!safe_forks(philo))
        return (0);
    print_fork(philo);

    pthread_mutex_lock(&philo->data->forks[right_fork]);
    set_fork_locked(philo->data, right_fork, 1);
    if (!safe_forks(philo))
        return (0);
    print_fork(philo);

    return (1);
}

void take_forks(t_philo *philo)
{
	if (is_running(philo->data))
	{
		if (philo->id % 2 == 0)
		{
			if (!touch_fork(philo, philo->left_fork, philo->right_fork))
				return;
		}
		else
		{
			if (!touch_fork(philo, philo->right_fork, philo->left_fork))
				return;
		}
	}
}
