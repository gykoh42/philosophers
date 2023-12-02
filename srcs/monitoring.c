/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:47:46 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/02 20:48:19 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_last_eat_time(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(philo->p_eat_time));
	if ((ft_get_time() - philo->last_eat_time) >= info->time_to_die)
	{
		pthread_mutex_unlock(&(philo->p_eat_time));
		ft_philo_dead_printf(info, philo->idx);
		finish_flag_on(info);
		return (0);
	}
	pthread_mutex_unlock(&(philo->p_eat_time));
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
		pthread_mutex_lock(&(info->finished_philo));
		if ((info->must_eat_cnt != 0) && \
				(info->finished_philo_cnt == info->num_of_philo))
		{
			pthread_mutex_unlock(&(info->finished_philo));
			break ;
		}
		pthread_mutex_unlock(&(info->finished_philo));
		usleep(500);
	}
}
