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

void	*routine(void *arg)
{
	struct timeval	death;
	struct timeval	current;
	t_data			*data;

	data = (t_data *)arg;
	gettimeofday(&death, NULL);
	printf("start: %ld:%06ld\n\n", death.tv_sec, death.tv_usec);
	timeadd(&death, data->dtime);
	printf("death: %ld:%06ld\n\n", death.tv_sec, death.tv_usec);
	while (1)
	{
		gettimeofday(&current, NULL);
		if (islater(current, death))
		{
			printf("%ld%03ld X died\n", current.tv_sec, current.tv_usec / 1000);
			return (NULL);
		}
	}
	return (NULL);
}

void	philosophers(t_data *data)
{
	pthread_t	t1;

	printf("number of philosophers: %d\ntime to die: %d\ntime to eat: %d\ntime \
to sleep: %d\noption: %d\n\n", data->size, data->dtime, data->etime, data->stime,
		data->option);
	if (pthread_create(&t1, NULL, &routine, data) != 0)
		return ;
	if (pthread_join(t1, NULL) != 0)
		return ;
}

//may need to check for long int overflows
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
