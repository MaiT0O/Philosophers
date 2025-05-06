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

void	set_phi_to(char *activity, t_philo *philo)
{
	time_t	action_end_at;

	if (activity[0] == 'E')
		action_end_at = get_time_ms() + philo->data->time_to_eat;
	else if (activity[0] == 'S')
		action_end_at = get_time_ms() + philo->data->time_to_sleep;
	else if (activity[0] == 'T')
		action_end_at = get_time_ms() + 0;
	else if (activity[0] == 'D')
		action_end_at = get_time_ms() + philo->data->time_to_die;
	while (get_time_ms() < action_end_at)
	{
		if (is_running(philo->data) == false)
			break ;
		usleep(100);
	}
	if (activity[0] == 'E')
		philo->eat_count += 1;
}

void	print_statement(t_philo *philo, char *status)
{
	time_t	process_at;
	int		philo_id;

	pthread_mutex_lock(&philo->data->print);
	if (is_running(philo->data) == false)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	process_at = get_time_ms() - philo->data->start;
	philo_id = philo->id + 1;
	if (status[0] == 'D')
		printf("%ld %d %s\n", process_at, philo_id, "died");
	else if (status[0] == 'E')
		printf("%ld %d %s\n", process_at, philo_id, "is eating");
	else if (status[0] == 'S')
		printf("%ld %d %s\n", process_at, philo_id, "is sleeping");
	else if (status[0] == 'T')
		printf("%ld %d %s\n", process_at, philo_id, "is thinking");
	else if (status[0] == 'F')
		printf("%ld %d %s\n", process_at, philo_id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print);
}
