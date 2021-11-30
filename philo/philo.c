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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

//TODO free t in case of error
//TODO destroy mutexes
void	philosophers(t_data *data)
{
	pthread_t		*t;
	int				i;

	t = (pthread_t *)malloc(sizeof(pthread_t) * data->size);
	if (t == NULL)
		return ;
	i = -1;
	while (++i < data->size)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	while (i < data->size)
	{
		usleep(40);
		if (pthread_create(&t[i], NULL, &routine, data) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < data->size)
	{
		if (pthread_join(t[i], NULL) != 0)
			return ;
		i++;
	}
	free(t);
}

void	free_philo(t_data *data)
{
	free(data->forks);
	free(data->fstate);
	free(data->xmeals);
}

//TODO may need to check for long int overflows
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
	data.x = 1;
	data.option = -1;
	data.end = 0;
	if (ac == 6)
		data.option = ft_atoi(av[5]);
	data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.size);
	data.fstate = (int *)malloc(sizeof(int) * data.size);
	data.xmeals = (int *)malloc(sizeof(int) * data.size);
	if (data.forks == NULL || data.fstate == NULL || data.xmeals == NULL)
		return (-1);
	ft_bzero(data.fstate, sizeof(int) * data.size);
	ft_bzero(data.xmeals, sizeof(int) * data.size);
	philosophers(&data);
	free_philo(&data);
}
