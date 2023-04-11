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

static int ft_isdigit(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		//printf("%c\n",c[i]);
		if (!(c[i] >= '0' && c[i] <= '9'))
			return (0);
		i++;
	}
		return (1);
}

int	ft_input_check(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		//printf("atio: %d\n",ft_atoi(argv[i]));
		if (!ft_isdigit(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	//printf("ok\n");
	return (1);
}