/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:04:04 by javellis          #+#    #+#             */
/*   Updated: 2023/04/07 15:35:20 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef	PHILOSOPHERS_H
# define	PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

struct s_prog;

typedef struct	s_philo {
	long long		last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
	pthread_t		thread;
	int				id;
	struct s_prog	*prog;
} t_philo;

typedef struct	s_prog {
	int		num_of_philos;
	t_philo	*philos;
	int		ttd;
	int		tte;
	int		tts;
	int		num_of_eat;
	struct timeval time;
} t_prog;

int	ft_atoi(const char *str);

#endif