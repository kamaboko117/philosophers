/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <asaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:36:01 by asaboure          #+#    #+#             */
/*   Updated: 2021/11/25 12:49:15 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>

typedef struct s_time
{
	struct timeval	death;
	struct timeval	current;
}				t_time;

typedef struct s_data
{
	int				size;
	int				dtime;
	int				etime;
	int				stime;
	int				option;
	pthread_mutex_t	*forks;
	int				*fstate;
	int				x;
}				t_data;

int		ft_atoi(const char *str);
int		isnumber(char *str);
int		puterror(char *error);
void	timeadd(struct timeval *t, int ms);
int		islater(struct timeval t1, struct timeval t2);
void	ft_bzero(void *s, size_t n);
void	*routine(void *arg);
int		check_death(t_time t, int x);
int		try_forks(t_data *data, int x, struct timeval current);

#endif