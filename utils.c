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
