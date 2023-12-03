#include "philo.h"

int	check_die(t_philo *p)
{
	int i;
	while (1)
	{
		i = -1;
		// printf("m_counter : %d\n", p->info->m_counter);
		while (++i < p->info->count)
		{
			if (get_time() - p[i].last_eat > p->info->t_die)
			{
				print("is_die", &p[i]);
				return (1);
			}
		}
		usleep(100);
		if (p->info->meals && p->info->m_counter >= p->info->meals && p->info->count > 1)
			return (1);
	}
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->last_eat = get_time();
	// printf("eat %d die %d slepp %d\n", philo->t_eat, philo->t_die, philo->t_sleep);
	while (1)
	{
		take_fork(philo);
		if (philo->info->count == 1)
			return (NULL);
		feed_philo(philo);
		sleep_philo(philo);
	}
	return (NULL);
}

int	create_threads(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->info->count)
	{
		philos[i].ind = i + 1;
		// printf("\033[38;5;233munitializing philo %d\n", i + 1);
		if (pthread_create(&(philos[i].philo), NULL, philo_routine, &philos[i]))
		{
			printf("\033[38;5;196an error occured while creating threads");
			return (1);
		}
		if (pthread_detach((philos)[i].philo))
			return (0);
		usleep(800);
	}
	return (check_die(philos));
	return (0);
}

int	init_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	info->start_time = get_time();
	while (i < info->count)
	{
		philo[i].info = info;
		philo[i].eat_c = 0;
		if (i < info->count - 1)
			philo[i].r_fork = &philo[i + 1].l_fork;
		else
			philo[i].r_fork = &philo[0].l_fork;
		i++;
		philo[i].r_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(&philo[i].l_fork, NULL);
		pthread_mutex_init(philo[i].r_fork, NULL);
		pthread_mutex_init(&philo[i].eat_time, NULL);
		// (*philo)[i].r_fork = malloc(sizeof(pthread_mutex_t));
		// pthread_mutex_init((*philo)[i].r_fork, NULL);
	}
	if (create_threads(philo))
		return (1);
	return (0);
}