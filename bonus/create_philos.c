/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:47:23 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/05 05:47:25 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	*check_die(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (1)
	{
		sem_wait(philos->last_eat_s);
		if (get_time() > philos->last_eat + philos->info->t_die)
		{
			print("die", philos, 1);
			return (NULL);
		}
		sem_post(philos->last_eat_s);
		usleep(200);
	}
}

int	create_thread_check_try(t_philo *philos)
{
	if (pthread_create(&philos->info->monitor, NULL, check_meals,
			philos) != 0)
		return (1);
	if (pthread_detach(philos->info->monitor) != 0)
		return (1);
	return (0);
}

void	ft_kill(t_philo *philos)
{
	int	j;

	j = 0;
	while (j < philos->info->count)
	{
		if (philos[j].pid_philo != 0)
			kill(philos[j].pid_philo, SIGINT);
			j++;
	}
}

int	create_philos(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->info->count)
	{
		philos[i].pid_philo = fork();
		if (philos[i].pid_philo < 0)
			printf("Errorm while creating process");
		if (philos[i].pid_philo == 0)
			philo_routine(&philos[i]);
		usleep(100);
	}
	if (create_thread_check_try(philos))
		return (1);
	sem_wait(philos->info->die_s);
	ft_kill(philos);
	return (0);
}
