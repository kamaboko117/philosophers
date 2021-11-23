/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:36:01 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/23 14:52:19 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_data
{
	int	size;
	int	dtime;
	int	etime;
	int	stime;
	int	option;
}				t_data;

int	ft_atoi(const char *str);
int	isnumber(char *str);
int	puterror(char *error);

#endif