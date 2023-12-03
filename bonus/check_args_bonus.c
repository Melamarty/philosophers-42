#include "philo_bonus.h"

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

int check_args (int ac, char **av)
{
	while (ac > 1)
	{
		if (!is_nb(av[--ac]))
			return (1);
		if (ft_atoi(av[ac]) > INT_MAX || ft_atoi(av[ac]) < INT_MIN)
			return (1);
	}
	return (0);
}

int	init_info(int ac, char **av, t_info *info)
{
	if (ac < 5)
		return (1);
	info->count = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->meals = 0;
	if (!info->count || !info->t_die || !info->t_eat || !info->t_sleep)
		return (1);
	(ac == 6) && (info->meals = ft_atoi(av[5]));
	sem_unlink("/fork");
	info->fork = sem_open ("/fork", O_CREAT, 0644, info->count);
	sem_unlink("/msg");
	info->msg_s = sem_open ("/msg", O_CREAT, 0644, 1);
	sem_unlink("/eat");
	info->eat_s = sem_open ("/eat", O_CREAT, 0644, 1);
	sem_unlink("/last_eat");
	info->last_eat_s = sem_open ("/last_eat", O_CREAT, 0644, 1);
	sem_unlink("/die");
	info->die_s = sem_open ("/die", O_CREAT, 0644, 1);
	sem_unlink("/fin");
	info->fin = sem_open ("/fin", O_CREAT, 0644, 1);
	return (0);
}