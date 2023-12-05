/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:27:07 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/05 16:27:39 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg(int argc)
{
	if (!(argc == 5 || argc == 6))
		return (1);
	return (0);
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

void	finish_flag_on(t_info *info)
{
	pthread_mutex_lock(&(info->finish));
	info->finish_flag = 1;
	pthread_mutex_unlock(&(info->finish));
}

void	ft_free_thread(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
		pthread_join(philo[i++].thread, NULL);
	pthread_mutex_destroy(&(info->finish));
	pthread_mutex_destroy(&(info->finished_philo_mutex));
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&(philo[i].last_eat_time_mutex));
		pthread_mutex_destroy(&(info->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(info->print));
	free(philo);
	free(info->fork);
}

int	ft_atoi(char *str)
{
	size_t	i;
	size_t	rtn;

	i = 0;
	rtn = 0;
	if (!str || !*str)
		return (-1);
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
			return (-1);
		if (rtn > 2147483647 || rtn == 0)
			return (-1);
	}
	return (rtn);
}
