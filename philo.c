/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:21:58 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/23 12:22:25 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

int	usage(void)
{
	printf("Correct usage: ./philo number_of_philosophers time_to_die time to");
	printf("_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (-1);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!isnumber(av[i]))
			return (puterror("every argument should be a positive integer\n"));
	}
	return (1);
}

void	*routine(void)
{
	printf("test from threads\n");
	return (NULL);
}

void	philosophers(t_data *data)
{
	printf("number of philosophers: %d\ntime to die: %d\ntime to eat: %d\ntime \
to sleep: %d\noption: %d\n", data->size, data->dtime, data->etime, data->stime,
		data->option);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (usage());
	if (!check_args(ac, av))
		return (-1);
	data.size = ft_atoi(av[1]);
	data.dtime = ft_atoi(av[2]);
	data.etime = ft_atoi(av[3]);
	data.stime = ft_atoi(av[4]);
	data.option = -1;
	if (ac == 6)
		data.option = ft_atoi(av[5]);
	philosophers(&data);
}
