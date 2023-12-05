/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:25:55 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/05 15:46:14 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_argv(t_info *info, int argc, char **argv)
{
	memset(info, 0, sizeof(t_info));
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->must_eat_cnt = ft_atoi(argv[5]);
	if (info->num_of_philo < 0 || info->time_to_die < 0
		|| info->time_to_eat < 0 || info->time_to_sleep < 0
		|| info->must_eat_cnt < 0)
		return (1);
	return (0);
}

int	ft_init_info(t_info *info, int argc, char **argv)
{
	int	i;

	if (ft_init_argv(info, argc, argv))
		return (1);
	info->start_time = ft_get_time();
	info->fork = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!(info->fork))
	{
		free(info->fork);
		return (1);
	}
	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(info->print), NULL) || \
		pthread_mutex_init(&(info->finish), NULL))
		return (1);
	return (0);
}

int	ft_init_philo(t_info *info, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * info->num_of_philo);
	if (!philo)
	{
		free(philo);
		return (1);
	}
	memset(*philo, 0, sizeof(t_philo) * info->num_of_philo);
	while (i < info->num_of_philo)
	{
		(*philo)[i].info = info;
		(*philo)[i].idx = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % info->num_of_philo;
		if (pthread_mutex_init(&((*philo)[i].last_eat_time_mutex), NULL))
			return (1);
		i++;
	}
	return (0);
}
