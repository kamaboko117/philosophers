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

#include <pthread.h>
#include <stdio.h>

int	isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	puterror(char *error)
{
	printf("%s", error);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while(++i < ac)
	{
		if (!isnumber(av[i]))
			return (puterror("every argument should be a positive integer\n"));
	}
	return (1);
}

int	usage(void)
{
	printf("Correct usage: ./philo number_of_philosophers time_to_die ");
	printf("time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (-1);
}

void	*routine()
{
	printf("test from threads\n");
	return (NULL);
}

int main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (usage());
	if (!check_args(ac, av))
		return (-1);
}