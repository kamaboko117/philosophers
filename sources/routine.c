/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:17:36 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/25 14:32:21 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

void	philosopher_eat(t_data *data, struct timeval *death, struct timeval
	current, int x)
{
	printf("%ld%03ld %d is eating\n", current.tv_sec, current.tv_usec / 1000, x);
	timeadd(death, data->dtime + data->etime);
	usleep(data->etime);
	pthread_mutex_unlock(&data->forks[x - 1]);
	data->fstate[x - 1] = 0;
	if (x == data->size)
	{
		pthread_mutex_unlock(&data->forks[0]);
		data->fstate[0] = 0;
	}
	else
	{
		pthread_mutex_unlock(&data->forks[x]);
		data->fstate[x] = 0;
	}
	data->xmeals[x - 1]++;
}

void	philosopher_sleep(t_data *data, int x, t_time t)
{
	printf("%ld%03ld %d is sleeping\n", t.current.tv_sec, t.current.tv_usec
		/ 1000, x);
	usleep(data->stime);
}

void	philosopher_think(int x, t_time t)
{
	printf("%ld%03ld %d is thinking\n", t.current.tv_sec, t.current.tv_usec
		/ 1000, x);
}

int	checkoption(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->size)
	{
		if (data->xmeals[i] < data->option || data->option == -1)
			return (0);
		i++;
	}
	return (1);
}

void	*routine(void *arg)
{
	t_time	t;
	t_data	*data;
	int		x;

	data = (t_data *)arg;
	x = data->x;
	data->x++;
	gettimeofday(&t.death, NULL);
	timeadd(&t.death, data->dtime);
	while (69)
	{
		gettimeofday(&t.current, NULL);
		if (check_death(t, x))
			return (NULL);
		if (try_forks(data, x, t.current))
		{
			philosopher_eat(data, &t.death, t.current, x);
			if (checkoption(data))
				return (NULL);
			philosopher_sleep(data, x, t);
			philosopher_think(x, t);
		}
	}
	return (NULL);
}
