/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_timeout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:09:29 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/26 18:11:32 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

int	death_sleep(struct timeval *death, int x, t_data *data)
{
	struct timeval	current;
	int				ms;

	gettimeofday(&current, NULL);
	ms = (death->tv_sec - current.tv_sec) * 1000;
	ms += (death->tv_usec - current.tv_usec) / 1000;
	if (ms < 0)
		ms = 0;
	usleep(ms);
	ft_log("died", x, data);
	data->end = 1;
	return (1);
}

int	isdying(int ms, struct timeval *death, t_data *data, int x)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	timeadd(&t, ms);
	if (islater(t, *death))
		return (death_sleep(death, x, data));
	return (0);
}
