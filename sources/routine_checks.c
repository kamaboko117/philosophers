/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:47:33 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/25 12:49:53 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

int	try_forks(t_data *data, int x, struct timeval current)
{
	if (data->fstate[x - 1] == 0)
	{
		pthread_mutex_lock(&data->forks[x - 1]);
		data->fstate[x - 1] = 1;
		printf("%ld%03ld %d has taken a fork\n", current.tv_sec, current.tv_usec
			/ 1000, x);
		if (x == data->size && data->fstate[0] == 0)
		{
			pthread_mutex_lock(&data->forks[0]);
			data->fstate[0] = 1;
			printf("%ld%03ld %d has taken a fork\n", current.tv_sec, current
				.tv_usec / 1000, x);
			return (2);
		}
		else if (data->fstate[x] == 0)
		{
			pthread_mutex_lock(&data->forks[x]);
			data->fstate[x] = 1;
			printf("%ld%03ld %d has taken a fork\n", current.tv_sec, current
				.tv_usec / 1000, x);
			return (1);
		}
	}
	return (0);
}

int	check_death(t_time t, int x)
{
	if (islater(t.current, t.death))
	{
		printf("%ld%03ld %d died\n", t.current.tv_sec, t.current.tv_usec
			/ 1000, x);
		return (1);
	}
	return (0);
}
