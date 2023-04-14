/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:00:27 by javellis          #+#    #+#             */
/*   Updated: 2023/04/14 11:55:19 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long	ris;
	int	sign;

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


static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(long int nb)
{
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = nb * -1;
	}
	if (nb < 10)
	{
		ft_putchar((nb % 10) + 48);
		return ;
	}
	else
	{	
		ft_putnbr(nb / 10);
		ft_putchar((nb % 10) + 48);
	}	
}