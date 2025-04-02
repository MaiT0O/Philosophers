/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:23:01 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/02 15:09:55 by ebansse          ###   ########.fr       */
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

int	free_all(t_data *data, int flag)
{
	int	i;

	i = -1;
    while (++i < data->philo_count)
	{
		if (&data->forks[i] != NULL)
        	pthread_mutex_destroy(&data->forks[i]);
	}
	if (data->forks != NULL)
    	free(data->forks);
	if (flag == 1)
		return (0);
	if (&data->print != NULL)
    	pthread_mutex_destroy(&data->print);
	if (data->philos != NULL)
    	free(data->philos);
	return (0);
}

void join_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_count)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
	pthread_join(data->monitor_thread, NULL);
}

int validate_arguments(int argc, char **argv)
{
    int i;

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
