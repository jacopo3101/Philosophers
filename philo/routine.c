/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:08:48 by javellis          #+#    #+#             */
/*   Updated: 2023/04/17 15:18:25 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->pmutex);
	pthread_mutex_lock(&philo->prog->dmutex);
	if (philo->prog->death == 0)
		printf("%ld	%d is thinking\n",
			get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->dmutex);
	pthread_mutex_unlock(&philo->prog->pmutex);
}

static void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->pmutex);
	pthread_mutex_lock(&philo->prog->dmutex);
	if (philo->prog->death == 0)
		printf("%ld	%d is sleeping\n",
			get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->dmutex);
	pthread_mutex_unlock(&philo->prog->pmutex);
	usleep(philo->prog->tts * 1000);
}

void	*ft_routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) && philo->prog->num_of_philos > 1)
		usleep(1000);
	while (!ft_check_end(philo))
	{
		if (ft_check_end(philo))
			return (0);
		ft_think(philo);
		if (ft_check_end(philo))
			return (0);
		ft_eat(philo);
		if (ft_check_end(philo))
			return (0);
		ft_sleep(philo);
	}
	return (0);
}
