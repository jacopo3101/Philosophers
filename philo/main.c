/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:51:19 by javellis          #+#    #+#             */
/*   Updated: 2023/04/06 18:20:42 by javellis         ###   ########.fr       */
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
		prog->philos[i].last_meal = 0;
		pthread_mutex_init(&(prog->philos[i].r_fork), 0);

		if (i == prog->num_of_philos - 1)
		{
			printf("i: %d, i + 1: 0\n", i);
			prog->philos[i].l_fork = &prog->philos[0].r_fork;
		}
		else
		{
			printf("i: %d, i + 1: %d\n", i, i+1);
			prog->philos[i].l_fork = &prog->philos[i + 1].r_fork;
		}
		prog->philos[i].id = i + 1;
		i++;
	}
}

// void *ft_routine_philo(void *arg)
// {

// }

int main(int argc, char const **argv)
{
	t_prog prog;
	int i = 0;
	struct timeval tv;

	if (argc == 5 || argc == 6)
	{
		ft_prog_init(argc, argv, &prog);
		gettimeofday(&tv, 0);
		while (i < prog.num_of_philos)
		{
			printf("time: %ld\n", tv.tv_usec);
			printf("id: %d\n", prog.philos[i].id);
			i++;
			usleep(1000);
			// pthread_create(prog.philos[i]->thread, 0, &ft_routine_philo, );
		}
	}
	else
		printf("Wrong number of argument\n");
	return 0;
}
// †
