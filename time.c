/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:12:04 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/02 15:14:28 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
