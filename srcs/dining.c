/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 01:53:25 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/02 19:09:10 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_eating(t_info *info, t_philo *philo)
{
    pthread_mutex_lock((&info->fork[philo->right]));
    ft_philo_printf(info, philo->idx, FORK);
    if (info->num_of_philo != 1)
    {
        pthread_mutex_lock(&(info->fork[philo->left]));
		ft_philo_printf(info, philo->idx, FORK);
		ft_philo_printf(info, philo->idx, EAT);
        pthread_mutex_lock(&(philo->p_eat_time));
		philo->last_eat_time = ft_get_time();
        pthread_mutex_unlock(&(philo->p_eat_time));
		ft_pass_time((long long)info->time_to_eat, info);
		philo->eat_cnt++;
		pthread_mutex_unlock(&(info->fork[philo->left]));
    }
    pthread_mutex_unlock(&(info->fork[philo->right]));
}

void    *ft_thread(void *argv)
{
    t_info *info;
    t_philo *philo;

    philo = (t_philo *)argv;
    info = philo->info;
    pthread_mutex_lock(&(philo->p_eat_time));
    philo->last_eat_time = ft_get_time();
    pthread_mutex_unlock(&(philo->p_eat_time));
    if (philo->idx % 2 == 1)
        usleep(info->time_to_eat * 500);
    while (check_finish(info))
    {
        ft_eating(info, philo);
        if (info->must_eat_cnt == philo->eat_cnt)
        {
            pthread_mutex_lock(&(info->finished_philo));
            info->finished_philo_cnt++;
            pthread_mutex_unlock(&(info->finished_philo));
            break;
        }
        ft_philo_printf(info, philo->idx, SLEEP);
        ft_pass_time((long long)info->time_to_sleep, info);
        ft_philo_printf(info, philo->idx, THINK);
        usleep(200);
    }
    return (0);
}

void    finish_flag_on(t_info *info)
{
    pthread_mutex_lock(&(info->finish));
    info->finish_flag = 1;
    pthread_mutex_unlock(&(info->finish));
}

void ft_die_or_finish(t_info *info, t_philo *philo)
{
    int i;
    long long cur_time;

    while (check_finish(info))
    {
        i = 0;
        while (i < info->num_of_philo)
        {
            cur_time = ft_get_time();
            pthread_mutex_lock(&(philo[i].p_eat_time));
            if ((cur_time - philo[i].last_eat_time) >= info->time_to_die)
            {
                pthread_mutex_unlock(&(philo[i].p_eat_time));
                ft_philo_dead_printf(info, philo[i].idx);
                finish_flag_on(info);
                return;
            }
            pthread_mutex_unlock(&(philo[i].p_eat_time));
            i++;
        }
        pthread_mutex_lock(&(info->finished_philo));
        if ((info->must_eat_cnt != 0) && (info->finished_philo_cnt == info->num_of_philo))
        {
            pthread_mutex_unlock(&(info->finished_philo));
            break ;
        }
        pthread_mutex_unlock(&(info->finished_philo));
        usleep(500);
    }
}

void    ft_dining(t_info *info, t_philo *philo)
{
    int i;

    info->start_time = ft_get_time();
    i = 0;
    while (i < info->num_of_philo)
    {
        if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
        {
            ft_free_thread(info, philo);
            ft_error_exit("error: thread creation failed");
        }
        i++;
    }
    usleep(800);
    ft_die_or_finish(info, philo);
    i = 0;
    while (i < info->num_of_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    ft_free_thread(info, philo);
    printf("haha\n");
}
