/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 01:53:25 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/05 16:10:19 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eating(t_info *info, t_philo *philo)
{
	pthread_mutex_lock((&info->fork[philo->right]));
	ft_philo_printf(info, philo->idx, FORK);
	if (info->num_of_philo != 1)
	{
		pthread_mutex_lock(&(info->fork[philo->left]));
		ft_philo_printf(info, philo->idx, FORK);
		ft_philo_printf(info, philo->idx, EAT);
		ft_pass_time((long long)info->time_to_eat, info);
		pthread_mutex_lock(&(philo->last_eat_time_mutex));
		philo->last_eat_time = ft_get_time();
		pthread_mutex_unlock(&(philo->last_eat_time_mutex));
		philo->eat_cnt++;
		pthread_mutex_unlock(&(info->fork[philo->left]));
	}
	pthread_mutex_unlock(&(info->fork[philo->right]));
}

void	ft_philo_set(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_eat_time_mutex));
	philo->last_eat_time = ft_get_time();
	pthread_mutex_unlock(&(philo->last_eat_time_mutex));
	if (philo->idx % 2 == 1)
	{
		if (info->time_to_die < info->time_to_eat * 2)
			usleep(info->time_to_die * 500);
		else
			usleep(info->time_to_eat * 500);
	}
}

void	*ft_thread(void *argv)
{
	t_info	*info;
	t_philo	*philo;

	philo = (t_philo *)argv;
	info = philo->info;
	ft_philo_set(info, philo);
	while (check_finish(info))
	{
		ft_eating(info, philo);
		if (info->must_eat_cnt == philo->eat_cnt)
		{
			pthread_mutex_lock(&(info->finished_philo_mutex));
			info->finished_philo++;
			pthread_mutex_unlock(&(info->finished_philo_mutex));
			break ;
		}
		ft_philo_printf(info, philo->idx, SLEEP);
		ft_pass_time((long long)info->time_to_sleep, info);
		ft_philo_printf(info, philo->idx, THINK);
		usleep(500);
	}
	return (0);
}

int	ft_dining(t_info *info, t_philo *philo)
{
	int	i;

	info->start_time = ft_get_time();
	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
		{
			ft_free_thread(info, philo);
			return (1);
		}
		i++;
	}
	usleep(800);
	ft_monitoring(info, philo);
	ft_free_thread(info, philo);
	return (0);
}
