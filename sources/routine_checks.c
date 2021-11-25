/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:47:33 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/25 15:49:04 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

void	lock_fork(t_data *data, struct timeval current, int x)
{
	pthread_mutex_lock(&data->forks[x]);
	data->fstate[x] = 1;
	printf("%ld%03ld %d has taken a fork\n", current.tv_sec, current.tv_usec
		/ 1000, x);
}

int	try_forks(t_data *data, int x, struct timeval current)
{
	int	left;
	int	right;

	left = x - 1;
	right = x;
	if (right == data->size)
		right = 0;
	if (data->fstate[left] == 0 && data->fstate[right] == 0)
	{
		lock_fork(data, current, left);
		lock_fork(data, current, right);
		return(1);
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
