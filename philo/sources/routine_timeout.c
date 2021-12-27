/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_timeout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:09:29 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/29 16:25:50 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

int	death_sleep(t_time *t, int x, t_data *data)
{
	struct timeval	current;
	long int		ms;

	gettimeofday(&current, NULL);
	ms = (t->death.tv_sec - current.tv_sec) * 1000;
	ms += (t->death.tv_usec - current.tv_usec) / 1000;
	if (ms < 0)
		ms = 0;
	usleep(ms * 1000);
	pthread_mutex_lock(&data->m_end);
	ft_log("died", x, data);
	data->end = 1;
	pthread_mutex_unlock(&data->m_end);
	return (1);
}

int	isdying(int ms, t_time *time, t_data *data, int x)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	timeadd(&t, ms);
	if (islater(t, time->death))
		return (death_sleep(time, x, data));
	return (0);
}
