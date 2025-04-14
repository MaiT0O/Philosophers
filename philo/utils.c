/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:23:01 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/14 16:35:21 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	atoi_verif(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		sign++;
		if (sign == 2)
			return (-1);
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	return (i);
}

long	ft_atoi_custom(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = atoi_verif(str);
	if (i == -1)
		return (LONG_MIN);
	res = 0;
	sign = 1;
	if (str[i - 1] == '-')
		sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	res = res * sign;
	return (res);
}

int	validate_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi_custom(argv[i]) <= 0)
		{
			printf("%s\n", ERR_INVALID_ARGS);
			return (0);
		}
		i++;
	}
	return (1);
}

int	free_all(t_data *data, int flag)
{
	int	i;

	if (data->fork)
		free(data->fork);
	if (flag == 1)
		return (1);
	if (data->forks)
	{
		i = -1;
		while (++i < data->philo_count)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print);
	if (flag == 2)
		return (1);
	if (data->philos)
		free(data->philos);
	return (1);
}

void	end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
	free_all(data, 0);
	return ;
}
