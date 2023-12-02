/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:20:22 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/02 14:50:01 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#define FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "died"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_cnt;
    int finish;
    int finished_eat_cnt;
    long long start_time;
    pthread_mutex_t *fork;
    pthread_mutex_t print;
    
}   t_info;

typedef struct s_philo
{
    pthread_t   thread;
    t_info      *info; 
    int         idx;
    int         left;
    int         right;
    int         eat_cnt;
    long long   last_eat_time;
}   t_philo;

/* init.c */
void    ft_init_info(t_info *info, int argc, char **argv);
void    ft_init_philo(t_info *info, t_philo **philo);

/* time.c */
long long ft_get_time(void);
void    ft_pass_time(long long wait_time, t_info *info);

/* dining.c */
void    ft_eat(t_info *info, t_philo *philo);
void    *ft_thread(void *argv);
void    ft_die_or_finish(t_info *info, t_philo *philo);
void    ft_dining(t_info *info, t_philo *philo);

/* utils.c */
void    ft_error_exit(char *str);
void    ft_check_arg(int argc);
void    ft_philo_printf(t_info *info, int idx, char *str);
void    ft_free_thread(t_info *info, t_philo *philo);
int     ft_atoi(char *str);

#endif