/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:13:34 by gykoh             #+#    #+#             */
/*   Updated: 2023/12/05 15:15:00 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	ft_check_arg(int argc)
{
	if (!(argc == 5 || argc == 6))
		return (1);
	return (0);
}
