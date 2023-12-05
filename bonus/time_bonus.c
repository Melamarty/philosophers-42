/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:46:49 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/05 05:46:50 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_philo(long time)
{
	long	now;

	now = get_time();
	while (get_time() < now + time)
		usleep(100);
}

long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}


void	*check_meals(void *args)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)args;
	while (philos->info->count > i)
	{
		sem_wait(philos->info->fin);
		i++;
	}
	sem_post(philos->info->die_s);
	close_sems(philos);
	return (NULL);
}