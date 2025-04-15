/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:44:21 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/15 12:44:19 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", correct_time(philo->data), philo->id, MSG_TAKE_FORK);
	pthread_mutex_unlock(&philo->data->print);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", correct_time(philo->data), philo->id, MSG_DIED);
	pthread_mutex_unlock(&philo->data->print);
}

void	print_meal(t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("%ld all philosophers have had enough to eat\n", correct_time(data));
	pthread_mutex_unlock(&data->print);
}
