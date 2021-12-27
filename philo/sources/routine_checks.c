/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:47:33 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/30 16:17:55 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

void	lock_fork(t_data *data, int fork, int x)
{
	pthread_mutex_lock(&data->forks[fork]);
	data->fstate[fork] = 1;
	ft_log("has taken a fork", x, data);
}

int	check_greed(t_data *data, int x)
{
	int	left;
	int	right;

	x--;
	left = x - 1;
	right = x + 1;
	if (left == -1)
		left = data->size - 1;
	if (right == data->size)
		right = 0;
	if (data->xmeals[left] < data->xmeals[x] || data->xmeals[right]
		< data->xmeals[x])
		return (1);
	return (0);
}

int	try_forks(t_data *data, int x)
{
	int	left;
	int	right;

	if (data->size == 1 && data->fstate[0] == 0)
	{
		lock_fork(data, 0, 1);
		return (0);
	}
	left = x - 1;
	right = x;
	if (right == data->size)
		right = 0;
	if (data->fstate[left] == 0 && data->fstate[right] == 0 && !check_greed(
			data, x))
	{
		lock_fork(data, left, x);
		lock_fork(data, right, x);
		return (1);
	}
	return (0);
}

int	check_death(t_data *data, t_time t, int x)
{
	struct timeval	current;

	if (data->end)
		return (1);
	gettimeofday(&current, NULL);
	if (islater(current, t.death))
	{
		pthread_mutex_lock(&data->m_end);
		ft_log("died", x, data);
		data->end = 1;
		pthread_mutex_unlock(&data->m_end);
		return (1);
	}
	return (0);
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
