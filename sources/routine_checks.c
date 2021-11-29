/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:47:33 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/29 16:27:50 by asaboure         ###   ########.fr       */
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

int	try_forks(t_data *data, int x)
{
	int	left;
	int	right;

	left = x - 1;
	right = x;
	if (right == data->size)
		right = 0;
	if (data->fstate[left] == 0 && data->fstate[right] == 0)
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
		ft_log("died", x, data);
		data->end = 1;
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
