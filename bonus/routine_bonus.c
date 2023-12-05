/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:46:53 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/05 05:46:56 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_fork(t_philo *philo)
{
	sem_wait(philo->info->fork);
	print("has taken a fork", philo, 0);
	if (philo->info->count == 1)
	{
		sem_post(philo->info->fork);
		wait_philo(philo->info->t_die);
		print("die", philo, 1);
		return (1);
	}
	sem_wait(philo->info->fork);
	print("has taken a fork", philo, 0);
	return (0);
}

void	sleep_philo(t_philo *philo)
{
	print("is sleeping", philo, 0);
	wait_philo(philo->info->t_sleep);
	print("is thinking", philo, 0);
}

int	feed_philo(t_philo *philo)
{
	print("is eating", philo, 0);
	sem_wait(philo->last_eat_s);
	philo->meals_count++;
	philo->last_eat = get_time();
	sem_post(philo->last_eat_s);
	wait_philo(philo->info->t_eat);
	sem_post(philo->info->fork);
	sem_post(philo->info->fork);
	if (philo->meals_count == philo->info->meals)
		sem_post(philo->info->fin);
	return (0);
}

void	print(char *str, t_philo *philo, int someone_died)
{
	sem_wait(philo->info->msg);
	printf("%ld\t%d\t%s\n", get_time() - philo->info->start,
		philo->ind, str);
	if (someone_died)
	{
		sem_post(philo->last_eat_s);
		sem_post(philo->info->die_s);
		close_sems(philo);
	}
	else
		sem_post(philo->info->msg);
}