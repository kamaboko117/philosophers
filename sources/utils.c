/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:36:12 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/23 17:20:12 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <limits.h>
#include <stdio.h>

int	ft_atoi(const char *str)
{
	unsigned long	i;
	long long int	ret;
	int				sign;

	i = 0;
	ret = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - 48);
		if (ret * sign > INT_MAX)
			return (-1);
		if (ret * sign < INT_MIN)
			return (0);
		i++;
	}
	return (ret * sign);
}

int	isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	puterror(char *error)
{
	printf("%s", error);
	return (0);
}

int	islater(struct timeval t1, struct timeval t2)
{
	if (t1.tv_sec > t2.tv_sec)
		return (1);
	if (t1.tv_sec == t2.tv_sec && t1.tv_usec > t2.tv_usec)
		return (1);
	return (0);
}

void	timeadd(struct timeval *t, int ms)
{
	ms *= 100;
	t->tv_usec += ms % 1000000;
	t->tv_sec += ms / 1000000;
}
