/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:28:39 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/05 16:12:57 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks(void)
{
	system("leaks --list philo");
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;

	atexit(leaks);
	if (ft_check_arg(argc))
		return (ft_error("error: invalid argument"));
	if (ft_init_info(&info, argc, argv))
		return (ft_error("error: invalid info"));
	if (ft_init_philo(&info, &philo))
		return (ft_error("error: invalid philo"));
	if (ft_dining(&info, philo))
		return (ft_error("error: invalid dining"));
	return (0);
}
