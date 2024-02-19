/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:41:56 by javellis          #+#    #+#             */
/*   Updated: 2023/04/17 17:24:52 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_end(t_philo *philo)
{
	int	res;
	
	pthread_mutex_lock(&philo->prog->dmutex);
	if (ft_count_eats(philo->prog) || philo->prog->death >= 1)
		res = 1;
	else
		res = 0;
	pthread_mutex_unlock(&philo->prog->dmutex);
	return (res);
}

int	ft_count_eats(t_prog *prog)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_lock(&prog->eat_mutex);
		if (prog->philos[i].meal_eated >= prog->num_of_eat)
			count++;
		pthread_mutex_unlock(&prog->eat_mutex);
		i++;
	}
	if (count == prog->num_of_philos)
		return (1);
	else
		return (0);
}

static void	ft_death(t_prog *prog, int i)
{
	pthread_mutex_unlock(&prog->meal);
	pthread_mutex_lock(&(prog->dmutex));
	prog->death++;
	pthread_mutex_unlock(&(prog->dmutex));
	pthread_mutex_lock(&prog->pmutex);
	printf("%ld	%d died\n", get_current_time(prog->time),
		prog->philos[i].id);
	pthread_mutex_unlock(&prog->pmutex);
}

void	*check_death(void *arg)
{
	int		i;

	while (((t_prog *)arg)->num_of_philos)
	{
		i = -1;
		usleep(1000);
		while (++i < ((t_prog *)arg)->num_of_philos)
		{
			pthread_mutex_lock(&((t_prog *)arg)->meal);
			if (((t_prog *)arg)->ttd < (get_current_time(((t_prog *)arg)->time)
					- ((t_prog *)arg)->philos[i].last_meal))
			{
				ft_death(((t_prog *)arg), i);
				return (0);
			}
			else if (ft_count_eats(((t_prog *)arg)))
			{
				pthread_mutex_unlock(&((t_prog *)arg)->meal);
				return (0);
			}
			pthread_mutex_unlock(&((t_prog *)arg)->meal);
		}
	}
	return (0);
}
