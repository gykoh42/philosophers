/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:12:39 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/02 20:22:12 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_dead_printf(t_info *info, int idx)
{
	long long	cur_time;

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

void	ft_philo_printf(t_info *info, int idx, char *str)
{
	long long	cur_time;

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
