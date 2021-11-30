/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:17:36 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/30 14:54:13 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

void	philosopher_eat(t_data *data, t_time *t, int x)
{
	int	left;
	int	right;

	left = x - 1;
	right = x;
	if (right == data->size)
		right = 0;
	ft_log("is eating", x, data);
	gettimeofday(&t->death, NULL);
	timeadd(&t->death, data->dtime);
	if (isdying(data->etime, t, data, x))
		return ;
	usleep(data->etime * 1000);
	pthread_mutex_unlock(&data->forks[left]);
	data->fstate[left] = 0;
	pthread_mutex_unlock(&data->forks[right]);
	data->fstate[right] = 0;
	data->xmeals[x - 1]++;
}

void	philosopher_sleep(t_data *data, int x, t_time *t)
{
	ft_log("is sleeping", x, data);
	if (isdying(data->stime, t, data, x))
		death_sleep(t, x, data);
	usleep(data->stime * 1000);
}

void	philosopher_think(t_data *data, int x)
{
	ft_log("is thinking", x, data);
	usleep(800);
}

void	init_routine(struct timeval *death, int x, t_data *data)
{
	gettimeofday(death, NULL);
	timeadd(death, data->dtime);
	if (x == 1)
		gettimeofday(&data->start, NULL);
}

void	*routine(void *arg)
{
	t_time	t;
	t_data	*data;
	int		x;

	data = (t_data *)arg;
	x = data->x;
	data->x++;
	init_routine(&t.death, x, data);
	usleep(50 * (x - 1));
	while (69)
	{
		if (check_death(data, t, x))
			return (NULL);
		if (try_forks(data, x))
		{
			philosopher_eat(data, &t, x);
			if (checkoption(data))
				return (NULL);
			philosopher_sleep(data, x, &t);
			philosopher_think(data, x);
		}
		usleep(200);
	}
	return (NULL);
}
