/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:28:39 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/02 02:43:35 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_info info;
    t_philo *philo;

    ft_check_arg(argc);
    ft_init_info(&info, argc, argv);
    ft_init_philo(&info, &philo);
    ft_dining(&info, philo);
    return (0);
}
