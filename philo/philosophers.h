/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <javellis@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:04:04 by javellis          #+#    #+#             */
/*   Updated: 2023/04/11 17:10:02 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef	PHILOSOPHERS_H
# define	PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>

struct s_prog;

typedef struct	s_philo {
	long int		last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	pthread_t		thread;
	int				id;
	int				meal_eated;
	struct s_prog	*prog;
} t_philo;

typedef struct	s_prog {
	int			num_of_philos;
	t_philo		*philos;
	int			ttd;
	int			tte;
	int			tts;
	int			exit_condition;
	int			num_of_eat;
	long int	time;
} t_prog;

int	ft_atoi(const char *str);
int	is_dead(t_philo	*philo);
int ft_check_end(t_philo *philo);
int	ft_input_check(int argc, char **argv);
#endif