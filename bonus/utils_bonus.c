/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:30:37 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/03 17:09:14 by mel-amar         ###   ########.fr       */
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

void	wait_p(int	time)
{
	usleep(time * 1000);
}

long get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_destroy(t_info *info)
{
	sem_close (info->fork);
	sem_close (info->msg_s);
	sem_close (info->eat_s);
	sem_close (info->last_eat_s);
	sem_close (info->die_s);
	return (0);
}