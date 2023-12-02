/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:27:07 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/02 19:29:50 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}
void ft_check_arg(int argc)
{
	if (!(argc == 5 || argc == 6))
		ft_error_exit("error: invalid argument");
}

int	check_finish(t_info *info)
{
	pthread_mutex_lock(&(info->finish));
	if (info->finish_flag == 1)
	{
		pthread_mutex_unlock(&(info->finish));
		return (0);
	}
	pthread_mutex_unlock(&(info->finish));
	return (1);
}

void	ft_philo_dead_printf(t_info *info, int idx)
{
	long long   cur_time;

	pthread_mutex_lock(&(info->print));
	cur_time = ft_get_time();
	if (info->no_print == 1)
	{
		pthread_mutex_unlock((&info->print));
		return ;
	}
	info->no_print = 1;
	printf("%lld %d %s\n", (cur_time - info->start_time), idx + 1, DIE);
	pthread_mutex_unlock((&info->print));
}

void ft_philo_printf(t_info *info, int idx, char *str)
{
	long long cur_time;

	pthread_mutex_lock(&(info->print));
	cur_time = ft_get_time();
	if (info->no_print == 1)
	{
		pthread_mutex_unlock((&info->print));
		return ;
	}
	printf("%lld %d %s\n", (cur_time - info->start_time), idx + 1, str);
	pthread_mutex_unlock((&info->print));
}

void    ft_free_thread(t_info *info, t_philo *philo)
{
	int i;

	// pthread_mutex_destroy(&(info->finish));
	// pthread_mutex_destroy(&(info->finished_philo));
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&(philo[i].p_eat_time));
		pthread_mutex_destroy(&(info->fork[i]));
		i++;
	}
	// pthread_mutex_destroy(&(info->print));
	free(philo);
	free(info->fork);
}

int ft_atoi(char *str)
{
	size_t  i;
	size_t rtn;

	i = 0;
	rtn = 0;
	if (!str || !*str)
		ft_error_exit("error: invalid argument");
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			rtn = rtn * 10 + (str[i] - '0');
			i++;
		}
		else
			ft_error_exit("error: invalid argument");
		if (rtn > 2147483647)
			ft_error_exit("error: invalid argument");
	}
	return (rtn);
}
