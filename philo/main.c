/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:51:19 by javellis          #+#    #+#             */
/*   Updated: 2023/04/07 17:23:24 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_prog_init(int argc, char const **argv, t_prog *prog)
{
	int	i;

	i = 0;
	prog->num_of_philos = ft_atoi(argv[1]);
	prog->ttd = ft_atoi(argv[2]);
	prog->tte = ft_atoi(argv[3]);
	prog->tts = ft_atoi(argv[4]);
	if (argc == 6)
		prog->num_of_eat = ft_atoi(argv[5]);
	else
		prog->num_of_eat = -1;
	prog->philos = (t_philo *)malloc(sizeof(t_philo) * prog->num_of_philos);
	while (i < prog->num_of_philos)
	{
		prog->philos[i].last_meal = prog->time;
		pthread_mutex_init(&(prog->philos[i].r_fork), 0);

		if (i == prog->num_of_philos - 1)
			prog->philos[i].l_fork = &prog->philos[0].r_fork;
		else
			prog->philos[i].l_fork = &prog->philos[i + 1].r_fork;
		prog->philos[i].id = i + 1;
		prog->philos[i].prog = prog;
		i++;
	}
}

// ft_think(t_prog *prog)
// {
// 	printf("%d %d is thinking")
// }

void	*ft_routine_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// printf("%d\n", philo->prog->ttd);
	// printf("ok\n");
	while(1)
	{
		// ft_eat(prog);
		// ft_sleep(prog);
		// ft_think(prog);
	}
	// if (philo % 2)
	// 	usleep(100000);
	return (0);
}

int main(int argc, char const **argv)
{
	t_prog prog;
	struct timeval tv;
	int i = 0;
	
	if (argc == 5 || argc == 6)
	{
		gettimeofday(&tv, 0);
		ft_prog_init(argc, argv, &prog);
		prog.time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
		while (i < prog.num_of_philos)
		{
			printf("id: %d\n", prog.philos[i].id);
			pthread_create(&(prog.philos[i].thread), 0, &ft_routine_philo, &(prog.philos[i]));
			i++;
		}
		i = 0;
		while (i < prog.num_of_philos)
		{
			pthread_join(prog.philos[i].thread, NULL);
			i++;
		}
		usleep(1000);
		
	}
	else
		printf("Wrong number of argument\n");
	return 0;
}
// †
