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
			return(0);
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
        // Vérifier si l'argument est un nombre valide
        if (!is_valid_number(argv[i]))
        {
            printf("%s\n", ERR_INVALID_ARGS);
            return (0);
        }

        // Convertir l'argument en entier et vérifier qu'il est > 0
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

int	free_all(t_data *data, int flag)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].last_eat_mutex);
	}
	free(data->forks);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->simulation_mutex);
	pthread_mutex_destroy(&data->philo_full_mutex);
	if (flag == 1)
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
