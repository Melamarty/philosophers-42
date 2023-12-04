#include "philo_bonus.h"

void	*check_die(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	sem_wait(philos->info->die_s);
	while (1)
	{
		sem_wait(philos->last_eat_s);
		if (get_time() > philos->last_eat + philos->info->t_die)
		{
			sem_post(philos->info->die_s);
			sem_post(philos->info->die_s);
			print("die", philos, 1);
			return (NULL);
		}
		sem_post(philos->last_eat_s);
		usleep(200);
	}
}

int	die_monitor(t_philo *philos)
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

	j = -1;
	while (++j < philos->info->count)
	{
		if (philos[j].philo != 0)
			kill(philos[j].philo, SIGINT);
		usleep(100);
	}
}

int	create_philosophers(t_philo *philos)
{
	int	i;

	i = -1;
	philos->info->start_time = get_time();
	while (++i < philos->info->count)
	{
		philos[i].philo = fork();
		if (philos[i].philo < 0)
			printf("Error: fork");
		if (philos[i].philo == 0)
			philo_routine(&philos[i]);
		usleep(100);
	}
	if (die_monitor(philos))
		return (1);
	sem_wait(philos->info->die_s);
	ft_kill(philos);
	return (0);
}

int	init_philos(t_philo *philos, t_info *info)
{
	int		i;

	i = -1;
	info->stop = 0;
	while (++i < info->count)
	{
		philos[i].ind = i + 1;
		philos[i].info = info;
		philos[i].eat_c = 0;
		sem_unlink("/last_eat");
		philos[i].last_eat_s = sem_open ("/last_eat", O_CREAT, 0644, 1);
	}
	create_philosophers(philos);
	return (0);
}