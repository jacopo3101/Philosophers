/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:51:19 by javellis          #+#    #+#             */
/*   Updated: 2023/04/17 17:12:05 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_current_time(long int start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - start_time);
}

static void	ft_philo_init(t_prog *prog, int i)
{
	pthread_mutex_lock(&prog->eat_mutex);
	prog->philos[i].meal_eated = 0;
	pthread_mutex_unlock(&prog->eat_mutex);
	pthread_mutex_lock(&prog->meal);
	prog->philos[i].last_meal = get_current_time(prog->time);
	pthread_mutex_unlock(&prog->meal);
	pthread_mutex_init(&(prog->philos[i].l_fork), 0);
	if (i == prog->num_of_philos - 1)
		prog->philos[i].r_fork = &prog->philos[0].l_fork;
	else
		prog->philos[i].r_fork = &prog->philos[i + 1].l_fork;
	prog->philos[i].id = i + 1;
	prog->philos[i].prog = prog;
}

static void	ft_prog_init(int argc, char const **argv, t_prog *prog)
{
	int				i;
	struct timeval	tv;

	i = -1;
	pthread_mutex_init(&(prog->meal), 0);
	pthread_mutex_init(&(prog->eat_mutex), 0);
	gettimeofday(&tv, 0);
	prog->time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	prog->num_of_philos = ft_atoi(argv[1]);
	prog->ttd = ft_atoi(argv[2]);
	prog->tte = ft_atoi(argv[3]);
	prog->tts = ft_atoi(argv[4]);
	prog->death = 0;
	if (argc == 6)
		prog->num_of_eat = ft_atoi(argv[5]);
	else
		prog->num_of_eat = -1;
	prog->philos = (t_philo *)malloc(sizeof(t_philo) * prog->num_of_philos);
	while (++i < prog->num_of_philos)
		ft_philo_init(prog, i);
	pthread_mutex_init(&(prog->dmutex), 0);
	pthread_mutex_init(&(prog->pmutex), 0);
}

int	main(int argc, char const **argv)
{
	t_prog	prog;
	int		i;

	i = -1;
	if (ft_input_check(argc, (char **)argv))
	{
		ft_prog_init(argc, argv, &prog);
		if (prog.num_of_philos != 1)
		{
			pthread_create(&prog.dthread, 0, &check_death, &prog);
			while (++i < prog.num_of_philos)
				pthread_create(&(prog.philos[i].thread),
					0, &ft_routine_philo, &(prog.philos[i]));
			i = -1;
			while (++i < prog.num_of_philos)
				pthread_join(prog.philos[i].thread, NULL);
			pthread_join(prog.dthread, NULL);
		}
		ft_free(prog);
	}
	return (0);
}
