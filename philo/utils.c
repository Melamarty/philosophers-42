/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:30:37 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/04 17:23:41 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

// void	wait_p(int	time)
// {
// 	usleep(time * 1000);
// }

void	wait_p(int ms)
{
	long	curr;

	curr = ms + get_time();
	while (get_time() < curr)
		usleep(100);
}
long get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	destroy_muts(t_philo *p)
{
	int	i;

	pthread_mutex_destroy(&p->info->meals_time);
	pthread_mutex_destroy(&p->info->msg_s);
	pthread_mutex_destroy(&p->info->last_time_s);
	pthread_mutex_destroy(&p->info->fin_m);
	i = -1;
	while (++i < p->info->count)
	{
		pthread_mutex_destroy(&p->l_fork);
		pthread_mutex_destroy(&p->eat_time);
	}
	return (0);
}