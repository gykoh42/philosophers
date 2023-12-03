/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:13:34 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/03 17:14:20 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	ft_check_arg(int argc)
{
	if (!(argc == 5 || argc == 6))
		ft_error_exit("error: invalid argument");
}
