#include "philo.h"

/*
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/
int	is_nb(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i++] == ' ');
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	while (str[i])
		if (str[i++] != ' ')
			return (0);
	return (1);
}

int check_args (int ac, char **av, t_info *info)
{
	if (ac == 6)
		info->meals = ft_atoi(av[5]);
	else
		info->meals = 0;
	while (ac > 1)
	{
		if (!is_nb(av[--ac]))
			return (1);
		if (ft_atoi(av[ac]) > INT_MAX || ft_atoi(av[ac]) < INT_MIN)
			return (1);
	}
	info->count = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->m_counter = 0;
	pthread_mutex_init(&info->msg_s, NULL);
	return (0);
}