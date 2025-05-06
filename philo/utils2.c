/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:06:09 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/28 16:38:45 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_list(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * (data->philo_count));
	if (!data->philos)
	{
		printf("%s\n", ERR_MEMORY_ALLOC);
		return (0);
	}
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_count);
	if (!data->forks)
	{
		free(data->philos);
		printf("%s\n", ERR_MEMORY_ALLOC);
		return (0);
	}
	return (1);
}

bool	is_dead(t_philo *philo)
{
	time_t	current_time;

	current_time = get_time_ms();
	if ((current_time - get_last_eat(philo)) > philo->data->time_to_die)
	{
		print_statement(philo, "DIED");
		stop_simulation(philo->data, false);
		return (true);
	}
	return (false);
}

time_t	get_time_ms(void)
{
	struct timeval	tv;
	long			res;

	if (gettimeofday(&tv, NULL) != 0)
	{
		printf("Error: Failed to get current time.\n");
		return (-1);
	}
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

void	sync_threads(time_t start_meeting_at)
{
	while (get_time_ms() < start_meeting_at)
		continue ;
}
