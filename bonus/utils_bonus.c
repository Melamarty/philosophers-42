/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:30:37 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/05 00:16:55 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

long	ft_atoi(const char *str)
{
	int			i;
	int long	res;
	int			s;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	s = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * s);
}

// void	wait_p(int ms)
// {
// 	long	curr;

// 	curr = ms + get_time();
// 	while (get_time() < curr)
// 		usleep(100);
// }
// long get_time()
// {
// 	struct timeval time;

// 	gettimeofday(&time, NULL);
// 	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
// }

// int	ft_destroy(t_philo *philo)
// {
// 	int i = -1;
// 	while (++i < philo->info->count)
// 	{
// 		// sem_close(philo[i].);
// 		sem_close (philo[i].last_eat_s);
// 	}
// 	sem_close (philo->info->fork);
// 	// sem_post(philo->info->msg_s);
// 	sem_close (philo->info->eat_s);
// 	sem_close(philo->info->fork);
// 	sem_close (philo->info->die_s);
// 	sem_close (philo->info->msg_s);
// 	sem_post (philo->info->fin);
// 	sem_close(philo->info->fin);
// 	return (0);
// }

void	*check_meals(void *args)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)args;
	while (philos->info->count > i)
	{
		// printf("entered \n");
		sem_wait(philos->info->fin);
		i++;
	}
	ft_kill(philos);
	sem_post(philos->info->die_s);
	close_sem(philos);
	return (NULL);
}

void	close_sem(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->info->count)
		sem_close(philos[i].last_eat_s);
	sem_post(philos->info->fin);
	sem_close(philos->info->fin);
	sem_close(philos->info->fork);
	sem_close(philos->info->die_s);
	// printf("finished\n");
	sem_close(philos->info->msg_s);
}

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
