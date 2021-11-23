/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:36:01 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/23 17:19:59 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>

typedef struct s_data
{
	int	size;
	int	dtime;
	int	etime;
	int	stime;
	int	option;
}				t_data;

int		ft_atoi(const char *str);
int		isnumber(char *str);
int		puterror(char *error);
void	timeadd(struct timeval *t, int ms);
int		islater(struct timeval t1, struct timeval t2);

#endif