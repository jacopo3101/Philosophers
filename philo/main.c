/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <javellis@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:51:19 by javellis          #+#    #+#             */
/*   Updated: 2023/04/11 18:10:09 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_current_time(long int start_time)
{
	struct timeval tv;

	gettimeofday(&tv, 0);
	//printf("start_time: %ld curr_time: %ld\n",start_time, ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000));
	return (((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - start_time);
}

int ft_check_end(t_philo *philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < philo->prog->num_of_philos)
	{
		//printf("mealeated :%d, num of eat: %d\n", philo->meal_eated , philo->prog->num_of_eat);
		if (philo->meal_eated == philo->prog->num_of_eat)
			count++;
		i++;
	}
	//printf("count :%d, numofphilos: %d\n", count , philo->prog->num_of_philos);
	if (is_dead(philo) || count == philo->prog->num_of_philos)
	{
	//	printf("ko\n");
		return (1);
	}
	else
	{
	//	printf("ok\n");
		return (0);
	}
}

int	is_dead(t_philo	*philo)
{
	//printf("id: %d, ttd: %d, currentTIme: %ld, lastmeal: %ld\n", philo->id, philo->prog->ttd, get_current_time(philo->prog->time), philo->last_meal);
	if (philo->prog->ttd < (get_current_time(philo->prog->time) - philo->last_meal))
	{
		philo->prog->exit_condition = 1;
		printf("%ld %d died\n", get_current_time(philo->prog->time), philo->id);
		return (1);
	}
	else
		return (0);
}

static void	ft_prog_init(int argc, char const **argv, t_prog *prog)
{
	int	i;
	struct timeval tv;

	i = 0;
	gettimeofday(&tv, 0);
	prog->time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	prog->num_of_philos = ft_atoi(argv[1]);
	prog->exit_condition = 0;
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
		prog->philos[i].meal_eated = 0;
		prog->philos[i].last_meal = get_current_time(prog->time);
		pthread_mutex_init(&(prog->philos[i].l_fork), 0);

		if (i == prog->num_of_philos - 1)
			prog->philos[i].r_fork = &prog->philos[0].l_fork;
		else
			prog->philos[i].r_fork = &prog->philos[i + 1].l_fork;
		prog->philos[i].id = i + 1;
		prog->philos[i].prog = prog;
		i++;
	}
}

void	ft_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_current_time(philo->prog->time), philo->id);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork r\n", get_current_time(philo->prog->time), philo->id);
	pthread_mutex_lock(&philo->l_fork);
	printf("%ld %d has taken a fork l\n", get_current_time(philo->prog->time), philo->id);
	printf("%ld %d is eating\n", get_current_time(philo->prog->time), philo->id);
	usleep(philo->prog->tte * 1000);
	philo->last_meal = get_current_time(philo->prog->time);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	philo->meal_eated++;
}

void	ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_current_time(philo->prog->time), philo->id);
	usleep(philo->prog->tts * 1000);
}


void	*ft_routine_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2) && philo->prog->num_of_philos > 1)
		usleep(philo->prog->tte * 1000);
	while(!philo->prog->exit_condition)
	{
		if (!ft_check_end(philo) && !philo->prog->exit_condition)
			ft_think(philo);
		else
			break ;
		if (!ft_check_end(philo) && !philo->prog->exit_condition)
			ft_eat(philo);
		else
			break ;
		//printf("sleep exit = %d || ft_end = %d\n",!philo->prog->exit_condition,!ft_check_end(philo));
		if (!ft_check_end(philo) && !philo->prog->exit_condition)
		{
			ft_sleep(philo);
		}
		else
			break ;
	}
	return (0);
}

int main(int argc, char const **argv)
{
	t_prog prog;
	int i = 0;
	
	if (argc == 5 || argc == 6)
	{
		if (ft_input_check(argc, (char **)argv))
		{
			ft_prog_init(argc, argv, &prog);
			if (prog.num_of_philos != 1)
			{
				while (i < prog.num_of_philos)
				{
					//printf("id: %d\n", prog.philos[i].id);
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
		}
		else
			printf("Error.\n");

	}
	else
		printf("Wrong argument number!\n");
	return 0;
}
// †
