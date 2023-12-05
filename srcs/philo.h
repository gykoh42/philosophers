/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:20:22 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/05 17:11:05 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_cnt;
	pthread_mutex_t	finish;
	int				finish_flag;
	pthread_mutex_t	finished_philo_mutex;
	int				finished_philo;
	long long		start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				dead_flag;

}	t_info;

typedef struct s_philo
{
	pthread_t		thread;
	t_info			*info;
	int				idx;
	int				left;
	int				right;
	int				eat_cnt;
	pthread_mutex_t	last_eat_time_mutex;
	long long		last_eat_time;
}	t_philo;

/* init.c */
int			ft_init_info(t_info *info, int argc, char **argv);
int			ft_init_philo(t_info *info, t_philo **philo);
int			ft_init_argv(t_info *info, int argc, char **argv);

/* dining.c */
void		ft_eating(t_info *info, t_philo *philo);
void		ft_philo_set(t_info *info, t_philo *philo);
void		*ft_thread(void *argv);
int			ft_dining(t_info *info, t_philo *philo);

/* monitoring.c */
int			ft_check_last_eat_time(t_info *info, t_philo *philo);
void		ft_monitoring(t_info *info, t_philo *philo);

/* printf.c */
void		ft_philo_dead_printf(t_info *info, int idx);
void		ft_philo_printf(t_info *info, int idx, char *str);

/* time.c */
long long	ft_get_time(void);
void		ft_pass_time(long long wait_time, t_info *info);

/* utils.c */
int			ft_check_arg(int argc);
int			check_finish(t_info *info);
void		finish_flag_on(t_info *info);
void		ft_free_thread(t_info *info, t_philo *philo);
int			ft_atoi(char *str);

#endif
