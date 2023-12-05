/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:47:46 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/05 13:09:53 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_last_eat_time(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_eat_time_mutex));
	if ((ft_get_time() - philo->last_eat_time) >= info->time_to_die)
	{
		pthread_mutex_unlock(&(philo->last_eat_time_mutex));
		ft_philo_dead_printf(info, philo->idx);
		finish_flag_on(info);
		return (0);
	}
	pthread_mutex_unlock(&(philo->last_eat_time_mutex));
	return (1);
}

void	ft_monitoring(t_info *info, t_philo *philo)
{
	int	i;

	while (check_finish(info))
	{
		i = 0;
		while (i < info->num_of_philo)
		{
			if (ft_check_last_eat_time(info, &philo[i]) == 0)
				return ;
			i++;
		}
		pthread_mutex_lock(&(info->finished_philo_mutex));
		if ((info->must_eat_cnt != 0) && \
				(info->finished_philo == info->num_of_philo))
		{
			pthread_mutex_unlock(&(info->finished_philo_mutex));
			break ;
		}
		pthread_mutex_unlock(&(info->finished_philo_mutex));
		usleep(500);
	}
}
