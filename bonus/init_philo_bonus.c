#include "philo_bonus.h"

int	ft_kill (t_philo *philos)
{
	int i;

	i = -1;
	while (++i < philos->info->count)
		kill(philos[i].philo, SIGINT);
	return (0);
}

void	*check_die(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	sem_wait (p->info->die_s);
	while (1)
	{
		// sem_wait(p->info->fin);
		// if (get_time() - p->last_eat > p->info->t_die)
		// 	printf("%d\n", p->info->stop);
		if (get_time() - p->last_eat > p->info->t_die && !p->info->stop)
		{
			if (!p->info->stop) {
				sem_wait(p->info->fin);
				p->info->stop = 1;
				sem_post(p->info->fin);
   				print("is die", p);
			}
			sem_post(p->info->die_s);
			sem_post(p->info->die_s);
			return (NULL);
		}
		// sem_post(p->info->fin);
		usleep(100);
	}
	return (NULL);
}

void	*philo_routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	sem_wait (philo->info->last_eat_s);
	philo->last_eat = get_time();
	sem_post (philo->info->last_eat_s);
	if (pthread_create(&philo->monitor, NULL, check_die, philo))
		return (NULL);
	if (pthread_detach(philo->monitor))
		return (NULL);
	// printf("eat %d die %d slepp %d\n", philo->t_eat, philo->t_die, philo->t_sleep);
	while (1)
	{
		take_fork(philo);
		if (philo->info->meals && philo->eat_c >= philo->info->meals)
			return (kill (philo->philo, SIGINT), NULL);
		feed_philo(philo);
		// printf("eated\n");
		sleep_philo(philo);
	}
	return (NULL);
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
		philos[i].philo = fork();
		philos[i].info->start_time = get_time();
		if (!philos[i].philo)
			philo_routine (&philos[i]);
		usleep(100);
	}
	// philos->info->die_s = sem_open ("/die", O_CREAT, 0644, 1);
	// philos->info->die_s = malloc(*)
	sem_wait(philos->info->die_s);
	// check_die(philos);
	ft_kill(philos);
	return (0);
}