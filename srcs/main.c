/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:28:39 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/05 16:25:36 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;

	if (ft_check_arg(argc))
		return (1);
	if (ft_init_info(&info, argc, argv))
		return (1);
	if (ft_init_philo(&info, &philo))
		return (1);
	if (ft_dining(&info, philo))
		return (1);
	return (0);
}
