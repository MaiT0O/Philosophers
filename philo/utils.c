/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:23:01 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/28 16:34:03 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(const char *str)
{
	int	i;
	int	sign_count;

	i = 0;
	sign_count = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (sign_count > 1)
			return (0);
		sign_count++;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atoi_custom(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			return (LONG_MIN);
		i++;
	}
	return (res * sign);
}

int	validate_arguments(int argc, char **argv)
{
	int		i;
	long	value;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("%s\n", ERR_INVALID_ARGS);
			return (0);
		}
		value = ft_atoi_custom(argv[i]);
		if (value <= 0 || value > INT_MAX)
		{
			printf("%s\n", ERR_INVALID_ARGS);
			return (0);
		}
		i++;
	}
	return (1);
}

int	free_all(t_data *data)
{
	int	i;

	if (!data)
		return (1);
	if (data->forks)
	{
		i = -1;
		while (++i < data->philo_count)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	if (data->philos)
	{
		i = -1;
		while (++i < data->philo_count)
			pthread_mutex_destroy(&data->philos[i].last_eat_mutex);
		free(data->philos);
	}
	if (!pthread_mutex_destroy(&data->print))
		printf("print mutex failed to destroy\n");
	if (!pthread_mutex_destroy(&data->simulation_mutex))
		printf("simulation mutex failed to destroy\n");
	if (!pthread_mutex_destroy(&data->philo_full_mutex))
		printf("philo_full mutex failed to destroy\n");
	if (!pthread_mutex_destroy(&data->start_mutex))
		printf("started_mutex failed to destroy\n");
	return (1);
}

int	end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	if (data->philo_count > 1)
		pthread_join(data->monitor_thread, NULL);
	usleep(1000000);
	debug_mutex(data);
	free_all(data);
	return (0);
}
