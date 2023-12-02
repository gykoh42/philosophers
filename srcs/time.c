/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 02:13:22 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/02 17:08:06 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long ft_get_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        ft_error_exit("error: gettimeofday failed");
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    ft_pass_time(long long operation_time, t_info *info)
{
    long long start_time;
    long long cur_time;

    start_time = ft_get_time();
    while (check_finish(info))
    {
        cur_time = ft_get_time();
        if ((cur_time - start_time) >= operation_time)
            break;
        usleep(100);
    }
}