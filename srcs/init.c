/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:25:55 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/02 20:21:14 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_info(t_info *info, int argc, char **argv)
{
	int	i;

	memset(info, 0, sizeof(t_info));
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->must_eat_cnt = ft_atoi(argv[5]);
	info->start_time = ft_get_time();
	info->fork = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!(info->fork))
		ft_error_exit("error: fork allocation failed");
	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL))
			ft_error_exit("error: mutex initialization failed");
		i++;
	}
	if (pthread_mutex_init(&(info->print), NULL) || \
		pthread_mutex_init(&(info->finish), NULL))
		ft_error_exit("error: mutex initialization failed");
}

void	ft_init_philo(t_info *info, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * info->num_of_philo);
	if (!philo)
		ft_error_exit("error: philo allocation failed");
	memset(*philo, 0, sizeof(t_philo) * info->num_of_philo);
	while (i < info->num_of_philo)
	{
		(*philo)[i].info = info;
		(*philo)[i].idx = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % info->num_of_philo;
		if (pthread_mutex_init(&((*philo)[i].p_eat_time), NULL))
			ft_error_exit("error: mutex initialization failed");
		i++;
	}
}
