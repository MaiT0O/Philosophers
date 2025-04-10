/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:06:09 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/08 16:43:03 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("%ld %d %s\n",get_time_ms(), philo->id, MSG_TAKE_FORK);
	pthread_mutex_unlock(philo->data->print);
}

void release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

int	safe_forks(t_philo *philo, int flag)
{
	if (!philo->data->simulation_running)
    {
    	if (philo->id % 2 == 0 && flag == 0)
            pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		else if (philo->id % 2 == 0 && flag == 1)
			release_forks(philo);
        else if (philo->id % 2 != 0 && flag == 0)
            pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		else if (philo->id % 2 != 0 && flag == 1)
			release_forks(philo);
		printf("philo[%d] release fork\n", philo->id);
        return (0);
    }
	return (1);
}

void take_forks(t_philo *philo)
{
	if (philo->data->simulation_running)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			if (!safe_forks(philo, 0))
				return ;
			print_fork(philo);
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			if (!safe_forks(philo, 1))
				return ;
			print_fork(philo);
		}
		else
		{
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			if (!safe_forks(philo, 0))
				return ;
			print_fork(philo);
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			if (!safe_forks(philo, 1))
				return ;
			print_fork(philo);
		}
	}
}

int is_dead(t_philo *philo)
{
    long	current_time;
	long	time_since_last_meal;

	current_time = get_time_ms();
    time_since_last_meal = current_time - philo->last_eat;

    if (time_since_last_meal > philo->data->time_to_die)
        return (1);
    return (0);
}

long	get_time_ms(void)
{
	struct timeval tv;
	long	res;

	if (gettimeofday(&tv, NULL) != 0)
    {
        printf("Error: Failed to get current time.\n");
        return (-1);
    }
    res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

void    print_death(t_philo *philo)
{
    pthread_mutex_lock(philo->data->print);
	printf("philophe[%d] hasn't eat since %ld ms\n", philo->id, get_time_ms() - philo->last_eat);
    printf("%ld %d %s\n", get_time_ms(), philo->id, MSG_DIED);
	pthread_mutex_unlock(philo->data->print);
}