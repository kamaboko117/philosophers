/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:09:10 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/29 19:52:42 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

//converts timeval structs to milliseconds
long	tvtms(struct timeval t)
{
	long	milliseconds;

	milliseconds = t.tv_sec * 1000;
	milliseconds += t.tv_usec / 1000;
	return (milliseconds);
}

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
	printf("%ld %d %s\n", t, x, s);
}

void	free_thread(pthread_t *t, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->size)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(t);
}
