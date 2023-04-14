/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:04:04 by javellis          #+#    #+#             */
/*   Updated: 2023/04/14 17:16:38 by javellis         ###   ########.fr       */
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
	int				death;
	int				num_of_philos;
	t_philo			*philos;
	int				ttd;
	int				tte;
	int				tts;
	int				num_of_eat;
	long int		time;
	pthread_t		dthread;
	pthread_mutex_t	dmutex;
	pthread_mutex_t	pmutex;
	pthread_mutex_t	meal;
	pthread_mutex_t	eat_mutex;
} t_prog;

int	ft_atoi(const char *str);
void	*check_death(void*	arg);
int ft_check_end(t_philo *philo);
int	ft_input_check(int argc, char **argv);
int	ft_count_eats(t_prog *prog);
void	ft_putnbr(long int nb);
#endif