/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:56 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/02 15:15:04 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        // Philosophe pair : prend d'abord la fourchette gauche
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
        pthread_mutex_unlock(&philo->data->print);
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
        pthread_mutex_unlock(&philo->data->print);
    }
    else
    {
        // Philosophe impair : prend d'abord la fourchette droite
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
        pthread_mutex_unlock(&philo->data->print);
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
        pthread_mutex_unlock(&philo->data->print);
    }
}

void release_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        // Philosophe pair : libère d'abord la fourchette gauche
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
    }
    else
    {
        // Philosophe impair : libère d'abord la fourchette droite
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
    }
}

void philosopher_think(t_philo *philo)
{
    long time_to_think;

    // Calculer le temps de réflexion en fonction du temps avant de mourir
    time_to_think = philo->data->time_to_die - (get_time_ms() - philo->last_eat) - philo->data->time_to_eat / 2;
    if (time_to_think < 0)
        time_to_think = 0;

    pthread_mutex_lock(&philo->data->print);
    printf("%ld %d %s\n", get_time_ms(), philo->id, MSG_THINKING);
    pthread_mutex_unlock(&philo->data->print);

    // Simuler le temps de réflexion
    usleep(time_to_think * 1000);
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < data->philo_count)
        {
            pthread_mutex_lock(&data->print);
            if (get_time_ms() - data->philos[i].last_eat > data->time_to_die)
            {
				usleep(10000);
                printf("%ld %d %s\n", get_time_ms(), data->philos[i].id, MSG_DIED);
                data->simulation_running = 0;
                pthread_mutex_unlock(&data->print);
                return (NULL);
            }
            pthread_mutex_unlock(&data->print);
            i++;
        }
        usleep(1000); // Vérifier périodiquement
    }
    return (NULL);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (philo->data->simulation_running && (philo->eat_count < philo->data->must_eat_count && philo->data->must_eat_count > 0))
    {
        take_forks(philo);

        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_EATING);
        pthread_mutex_unlock(&philo->data->print);
        philo->last_eat = get_time_ms();
        philo->eat_count++;
        usleep(philo->data->time_to_eat * 1000); // Simuler le temps pour manger
        release_forks(philo);

        philosopher_think(philo);

        pthread_mutex_lock(&philo->data->print);
        printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_SLEEPING);
        pthread_mutex_unlock(&philo->data->print);
        usleep(philo->data->time_to_sleep * 1000); // Simuler le temps pour dormir
    }
    return NULL;
}
