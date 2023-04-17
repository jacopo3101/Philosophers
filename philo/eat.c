/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:08:51 by javellis          #+#    #+#             */
/*   Updated: 2023/04/17 15:19:52 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_last_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->prog->pmutex);
	pthread_mutex_lock(&philo->prog->dmutex);
	if (philo->prog->death == 0)
		printf("%ld	%d has taken a fork r\n",
			get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->dmutex);
	pthread_mutex_unlock(&philo->prog->pmutex);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->prog->pmutex);
	pthread_mutex_lock(&philo->prog->dmutex);
	if (philo->prog->death == 0)
		printf("%ld	%d has taken a fork l\n",
			get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->dmutex);
	pthread_mutex_unlock(&philo->prog->pmutex);
}

static void	ft_default_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->prog->pmutex);
	pthread_mutex_lock(&philo->prog->dmutex);
	if (philo->prog->death == 0)
		printf("%ld	%d has taken a fork l\n",
			get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->dmutex);
	pthread_mutex_unlock(&philo->prog->pmutex);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->prog->pmutex);
	pthread_mutex_lock(&philo->prog->dmutex);
	if (philo->prog->death == 0)
		printf("%ld	%d has taken a fork r\n",
			get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->dmutex);
	pthread_mutex_unlock(&philo->prog->pmutex);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id == philo->prog->num_of_philos)
		ft_last_eat(philo);
	else
		ft_default_eat(philo);
	pthread_mutex_lock(&philo->prog->pmutex);
	pthread_mutex_lock(&philo->prog->dmutex);
	if (philo->prog->death == 0)
		printf("%ld	%d is eating\n",
			get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->dmutex);
	pthread_mutex_unlock(&philo->prog->pmutex);
	pthread_mutex_lock(&philo->prog->meal);
	philo->last_meal = get_current_time(philo->prog->time);
	pthread_mutex_unlock(&philo->prog->meal);
	usleep(philo->prog->tte * 1000);
	pthread_mutex_lock(&philo->prog->eat_mutex);
	philo->meal_eated++;
	pthread_mutex_unlock(&philo->prog->eat_mutex);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
