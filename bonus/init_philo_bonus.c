/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:47:08 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/05 05:47:11 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_sems(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->count)
	{
		sem_close(philos[i].last_eat_s);
		i++;
	}
	sem_post(philos->info->fin);
	sem_close(philos->info->fin);
	sem_close(philos->info->fork);
	sem_close(philos->info->die_s);
	sem_close(philos->info->msg);
}

void	philo_routine(t_philo *philo)
{
	philo->last_eat = get_time();
	if (pthread_create(&philo->info->monitor, NULL, check_die, philo) != 0)
		return ;
	if (pthread_detach(philo->info->monitor) != 0)
		return ;
	while (1)
	{
		if (take_fork(philo))
			exit(0);
		feed_philo(philo);
		sleep_philo(philo);
	}
	return ;
}

int	init_philo(t_philo *philos, t_info *info)
{
	int		i;

	i = 0;
	while (i < info->count)
	{
		philos[i].info = info;
		philos[i].meals_count = 0;
		philos[i].last_eat = 0;
		philos[i].ind = i + 1;
		sem_unlink("/last_eat");
		philos[i].last_eat_s = sem_open("/last_eat", O_CREAT, 0644, 1);
		if (philos[i].last_eat_s == SEM_FAILED)
		{
			printf("Error : semaphore");
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_sem(char *str, sem_t **sem_all, int i)
{
	sem_unlink(str);
	*sem_all = sem_open(str, O_CREAT, 0644, i);
	if (*sem_all == SEM_FAILED)
	{
		printf("error: sem_open\n");
		return (1);
	}
	return (0);
}

int	ft_init_ags(t_info *info, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		info->start = get_time();
		info->count = ft_atoi(av[1]);
		if (info->count == 0)
			return (1);
		info->t_die = ft_atoi(av[2]);
		if (info->t_die == 0)
			return (1);
		info->t_eat = ft_atoi(av[3]);
		if (info->t_eat == 0)
			return (1);
		info->t_sleep = ft_atoi(av[4]);
		if (info->t_sleep == 0)
			return (1);
		if (create_sem("/msg", &info->msg, 1))
			return (1);
		if (create_sem("/die", &info->die_s, 0))
			return (1);
		if (create_sem("/fork", &info->fork, info->count))
			return (1);
		if (create_sem("/fin", &info->fin, 0))
			return (1);
	}
	return (0);
}

int	init_info(t_info *info, char **av, int ac)
{
	int	i;

	if (ac == 6)
	{
		info->meals = ft_atoi(av[5]);
		if (info->meals == 0)
			return (1);
	}
	i = ft_init_ags(info, ac, av);
	return (i);
}