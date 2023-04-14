/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:51:19 by javellis          #+#    #+#             */
/*   Updated: 2023/04/14 17:19:47 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_current_time(long int start_time)
{
	struct timeval tv;

	gettimeofday(&tv, 0);
	// printf("start_time: %ld curr_time: %ld, result: %ld\n"
	// 	,start_time, ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000),((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - start_time);
	return (((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - start_time);
}

int ft_check_end(t_philo *philo)
{
	int	i;
	// int	count;
	int	res;

	i = 0;
	// count = 0;
	// while (i < philo->prog->num_of_philos)
	// {
	// 	// printf("mealeated :%d, num of eat: %d\n", philo->meal_eated , philo->prog->num_of_eat);
	// 	if (philo->meal_eated == philo->prog->num_of_eat)
	// 		count++;
	// 	i++;
	// }
	// printf("count :%d, numofphilos: %d\n", count , philo->prog->num_of_philos);
	pthread_mutex_lock(&philo->prog->dmutex);
	if (ft_count_eats(philo->prog) || philo->prog->death >= 1)
	{
		// write(1, "ok43\n", 5);
		res = 1;
	}
	else
		res = 0;
	pthread_mutex_unlock(&philo->prog->dmutex);
	return(res);
}

int	ft_count_eats(t_prog *prog)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < prog->num_of_philos)
	{
		//printf("mealeated :%d, num of eat: %d\n", prog->philos[i].meal_eated , prog->num_of_eat);

		pthread_mutex_lock(&prog->eat_mutex);
		if (prog->philos[i].meal_eated == prog->num_of_eat)
			count++;
		pthread_mutex_unlock(&prog->eat_mutex);
		i++;
	}
	// printf("count :%d, num_of_philos: %d\n", count , prog->num_of_philos);
	if (count == prog->num_of_philos)
		return (1);
	else
		return (0);
}

void	*check_death(void*	arg)
{
	t_prog	*prog;
	int		i;

	prog = (t_prog *)arg;
	while (prog->num_of_philos)
	{
		i = 0;
		usleep(1000);
		while (i < prog->num_of_philos)
		{
				// printf("id: %d, ttd: %d, currentTIme: %ld, lastmeal: %ld\n", 
				// 	prog->philos[i].id, prog->ttd, get_current_time(prog->time), prog->philos[i].last_meal);

			pthread_mutex_lock(&prog->meal);
			if (prog->ttd < (get_current_time(prog->time) - prog->philos[i].last_meal))
			{
				pthread_mutex_unlock(&prog->meal);
				pthread_mutex_lock(&(prog->dmutex));
				prog->death++;
				pthread_mutex_unlock(&(prog->dmutex));

				pthread_mutex_lock(&prog->pmutex);
				printf("%ld	%d died\n", get_current_time(prog->time), prog->philos[i].id);

				// ft_putnbr(get_current_time(prog->time));
				// write(1, "\t", 1);
				// ft_putnbr(prog->philos[i].id);
				// write(1, " died\n", 6);
				pthread_mutex_unlock(&prog->pmutex);

				return (0);
			}
			else if (ft_count_eats(prog))
			{
				pthread_mutex_unlock(&prog->meal);
				return (0);
			}
			pthread_mutex_unlock(&prog->meal);
			
			i++;	
		}
	}
	return (0);
}

static void	ft_prog_init(int argc, char const **argv, t_prog *prog)
{
	int	i;
	struct timeval tv;

	i = 0;
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
	while (i < prog->num_of_philos)
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
		i++;
	}
	pthread_mutex_init(&(prog->dmutex), 0);
	pthread_mutex_init(&(prog->pmutex), 0);
}

void	ft_think(t_philo *philo)
{
	// if (ft_check_end(philo))
	// 	return ;
	pthread_mutex_lock(&philo->prog->pmutex);
	// ft_putnbr(get_current_time(philo->prog->time));
	// write(1, "\t", 1);
	// ft_putnbr(philo->id);
	// write(1, " is thinking\n", 13);
	printf("%ld	%d is thinking\n", get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->pmutex);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	// if (ft_check_end(philo))
	// 	return ;

	pthread_mutex_lock(&philo->prog->pmutex);
	printf("%ld	%d has taken a fork r\n", get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->pmutex);

	// ft_putnbr(get_current_time(philo->prog->time));
	// write(1, "\t", 1);
	// ft_putnbr(philo->id);
	// write(1, " has taken a fork r\n", 20);

	pthread_mutex_lock(&philo->l_fork);
	// if (ft_check_end(philo))
	// 	return ;
	
	pthread_mutex_lock(&philo->prog->pmutex);
	printf("%ld	%d has taken a fork l\n", get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->pmutex);

	// ft_putnbr(get_current_time(philo->prog->time));
	// write(1, "\t", 1);
	// ft_putnbr(philo->id);
	// write(1, " has taken a fork l\n", 20);

	// if (ft_check_end(philo))
	// 	return ;
	pthread_mutex_lock(&philo->prog->pmutex);
	printf("%ld	%d is eating\n", get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->pmutex);

	// ft_putnbr(get_current_time(philo->prog->time));
	// write(1, "\t", 1);
	// ft_putnbr(philo->id);
	// write(1, " is eating\n", 11);

	// ft_putnbr(get_current_time(philo->prog->time));
	// write(1, "\t", 1);
	// ft_putnbr(philo->id);
	// write(1, " has taken a fork r\n", 20);

	pthread_mutex_lock(&philo->prog->meal);
	philo->last_meal = get_current_time(philo->prog->time);
	pthread_mutex_unlock(&philo->prog->meal);

	usleep(philo->prog->tte * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);

	pthread_mutex_lock(&philo->prog->eat_mutex);
	philo->meal_eated++;
	pthread_mutex_unlock(&philo->prog->eat_mutex);
}

void	ft_sleep(t_philo *philo)
{
	// if (ft_check_end(philo))
	// 	return ;
	pthread_mutex_lock(&philo->prog->pmutex);
	// ft_putnbr(get_current_time(philo->prog->time));
	// write(1, "\t", 1);
	// ft_putnbr(philo->id);
	// write(1, " is sleeping\n", 13);
	printf("%ld	%d is sleeping\n", get_current_time(philo->prog->time), philo->id);
	pthread_mutex_unlock(&philo->prog->pmutex);
	usleep(philo->prog->tts * 1000);
}

void	*ft_routine_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) && philo->prog->num_of_philos > 1)
		usleep(1000);
	while(!ft_check_end(philo))
	{
		// printf("id: %d, death: %d\n",philo->id, philo->prog->death);
		// if (ft_check_end(philo))
		// 	return (0);
		ft_think(philo);
		// printf("id: %d, death: %d\n",philo->id, philo->prog->death);

		// if (ft_check_end(philo))
		// 	return (0);
		ft_eat(philo);
		//printf("sleep exit = %d || ft_end = %d\n",!philo->prog->exit_condition,!ft_check_end(philo));
		// printf("id: %d, death: %d\n",philo->id, philo->prog->death);

		// if (ft_check_end(philo))
		// 	return (0);
		ft_sleep(philo);
	}
	return (0);
}

int main(int argc, char const **argv)
{
	t_prog prog;
	int i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		if (ft_input_check(argc, (char **)argv))
		{
			ft_prog_init(argc, argv, &prog);
			if (prog.num_of_philos != 1)
			{
				pthread_create(&prog.dthread, 0, &check_death, &prog);
				while (i < prog.num_of_philos)
				{
					pthread_create(&(prog.philos[i].thread), 0, &ft_routine_philo, &(prog.philos[i]));
					i++;
				}
				i = 0;
				while (i < prog.num_of_philos)
				{
					pthread_join(prog.philos[i].thread, NULL);
					i++;
				}
				pthread_join(prog.dthread, NULL);
				free(prog.philos);
			}
			pthread_mutex_destroy(&prog.dmutex);
        	pthread_mutex_destroy(&prog.pmutex);
        	pthread_mutex_destroy(&prog.eat_mutex);
			i = 0;
			while (i < prog.num_of_philos)
			{
				pthread_mutex_destroy(&prog.philos[i].l_fork);
				i++;
			}
		}
		else
			printf("Error.\n");
	}
	else
		printf("Wrong argument number!\n");
	return (0);
}