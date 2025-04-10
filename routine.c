/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:56 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/08 16:50:41 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philosopher_think(t_philo *philo)
{
    if (philo->data->simulation_running)
    {
        long time_to_think;
    
        // Calculer le temps de réflexion en fonction du temps avant de mourir
        time_to_think = (philo->data->time_to_die - (get_time_ms() - philo->last_eat) - philo->data->time_to_eat - philo->data->time_to_sleep) / 2;
		if (time_to_think < 0)
			time_to_think = 0;
		if (time_to_think == 0)
			time_to_think = 1;
    
        pthread_mutex_lock(philo->data->print);
        printf("%ld %d %s\n", get_time_ms(), philo->id, MSG_THINKING);
        pthread_mutex_unlock(philo->data->print);
    
        // Simuler le temps de réflexion
        usleep(time_to_think * 1000);
    }
    return ;
}

void philosopher_sleep(t_philo *philo)
{
    if (philo->data->simulation_running)
    {
        pthread_mutex_lock(philo->data->print);
        printf("%ld %d %s\n", get_time_ms(), philo->id, MSG_SLEEPING);
        pthread_mutex_unlock(philo->data->print);
        usleep(philo->data->time_to_sleep * 1000);
    }
    return ;
}

void	philosopher_eat(t_philo *philo)
{
    if (philo->data->simulation_running)
    {
        pthread_mutex_lock(philo->data->print);
		printf("philophe[%d] hasn't eat since %ld ms\n", philo->id, get_time_ms() - philo->last_eat);
        printf("%ld %d %s\n", get_time_ms(), philo->id, MSG_EATING);
        pthread_mutex_unlock(philo->data->print);
        philo->last_eat = get_time_ms();
        philo->eat_count++;
        usleep(philo->data->time_to_eat * 1000);
        if (philo->eat_count == philo->data->must_eat_count)
            philo->data->philo_full++;
    }
    return ;
}

void    stop_sim(t_data *data, int flag, int i)
{
	usleep(10000);
	data->simulation_running = 0;
    pthread_mutex_lock(data->print);
	if (flag == 1)
		printf("tous les philosophes ont manger a leur faim\n");
	else if (flag == 0)
		data->philos[i].death = 1;
	pthread_mutex_unlock(data->print);
    return ;
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        i = -1;
        while (++i < data->philo_count)
        {
            if (data->philo_full == data->philo_count)
                stop_sim(data, 1, i);
            else if (is_dead(&data->philos[i]))
                stop_sim(data, 0, i);
            if (!data->simulation_running)
                return (NULL);
        }
        usleep(1000); // Vérifier périodiquement
    }
    return (NULL);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (philo->data->simulation_running)
    {
        if (!philo->data->simulation_running)
            break;
        take_forks(philo);
        if (!philo->data->simulation_running)
        {
            release_forks(philo);
            break;
        }
        philosopher_eat(philo);
        release_forks(philo);
        if (!philo->data->simulation_running)
            break;
        philosopher_think(philo);
        if (!philo->data->simulation_running)
            break;
        philosopher_sleep(philo);
    }
	if (philo->death == 1)
		print_death(philo);
    return (NULL);
}
