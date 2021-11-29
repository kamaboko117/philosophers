/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:09:10 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/29 16:32:21 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
