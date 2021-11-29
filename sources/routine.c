/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:17:36 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/29 16:31:38 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <unistd.h>

void	ft_log(char *s, int x, t_data *data)
{
	struct timeval	current;
	long			t;
	long			ms_start;

	if (data->end)
		return ;
	gettimeofday(&current, NULL);
	t = tvtms(current);
	ms_start = tvtms(data->start);
	t -= ms_start;
	(void)ms_start;
	printf("%ld %d %s\n", t, x, s);
}

void	philosopher_eat(t_data *data, t_time *t, int x)
{
	ft_log("is eating", x, data);
	gettimeofday(&t->death, NULL);
	timeadd(&t->death, data->dtime);
	if (isdying(data->etime, t, data, x))
		return ;
	usleep(data->etime * 1000);
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

void	philosopher_sleep(t_data *data, int x)
{
	ft_log("is sleeping", x, data);
	usleep(data->stime * 1000);
}

void	philosopher_think(t_data *data, int x)
{
	ft_log("is thinking", x, data);
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
	if (x == 1)
		gettimeofday(&data->start, NULL);
	while (69)
	{
		if (check_death(data, t, x))
			return (NULL);
		if (try_forks(data, x))
		{
			philosopher_eat(data, &t, x);
			if (checkoption(data))
				return (NULL);
			philosopher_sleep(data, x);
			philosopher_think(data, x);
		}
	}
	return (NULL);
}
