/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:00:27 by javellis          #+#    #+#             */
/*   Updated: 2023/04/17 17:01:37 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long	ris;
	int		sign;

	if (!str)
		return (0);
	ris = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		ris = ris * 10 + *str - '0';
		str++;
	}
	if (ris > INT_MAX)
	{
		return (-1);
	}
	return (ris * sign);
}

void	ft_free(t_prog prog)
{
	int	i;

	pthread_mutex_destroy(&prog.dmutex);
	pthread_mutex_destroy(&prog.pmutex);
	pthread_mutex_destroy(&prog.eat_mutex);
	pthread_mutex_destroy(&prog.meal);
	i = 0;
	while (i < prog.num_of_philos)
	{
		pthread_mutex_destroy(&prog.philos[i].l_fork);
		i++;
	}
	free(prog.philos);
}
