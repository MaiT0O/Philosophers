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
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_statement(philo, "Fork");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_statement(philo, "Fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_statement(philo, "Fork");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_statement(philo, "Fork");
	}
}
