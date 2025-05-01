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

int	take_forks(t_philo *philo)
{
    if (is_running(philo->data))
    {
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
            if (!is_running(philo->data)) // Vérifier après le verrouillage
            {
                pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
                return (0);
            }
            print_fork(philo);

            pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
            if (!is_running(philo->data)) // Vérifier après le verrouillage
            {
                release_forks(philo);
                return (0);
            }
            print_fork(philo);
        }
        else
        {
            pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
            if (!is_running(philo->data)) // Vérifier après le verrouillage
            {
                pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
                return (0);
            }
            print_fork(philo);

            pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
            if (!is_running(philo->data)) // Vérifier après le verrouillage
            {
                release_forks(philo);
                return (0);
            }
            print_fork(philo);
        }
    }
    return (1);
}

void	release_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
    pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}
