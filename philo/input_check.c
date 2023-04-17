/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <javellis@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:17:42 by javellis          #+#    #+#             */
/*   Updated: 2023/04/11 16:17:42 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!(c[i] >= '0' && c[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_input_check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong argument number!\n");
		return (0);
	}
	while (i < argc)
	{
		if (!ft_isdigit(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			printf("Error.\n");
			return (0);
		}
		i++;
	}
	return (1);
}
