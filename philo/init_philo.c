#include "philo.h"

int	check_die(t_philo *p)
{
	int i;
	while (1)
	{
		i = -1;
		while (++i < p->count)
		if (get_time() - p[i].last_eat > p->t_die)
		{
			printf("philo %d is die\n", p[i].ind);
			return (1);
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// printf("eat %d die %d slepp %d\n", philo->t_eat, philo->t_die, philo->t_sleep);
	while (1)
	{
		take_fork(philo);
		feed_philo(philo);
		sleep_philo(philo);
		sleep(1);
	}
	return (NULL);
}

int	create_threads(t_philo **philo)
{
	int	i;

	i = 0;
	// printf("%d\n", (*philo)->count);
	while (i < (*philo)->count)
	{
		(*philo)[i].ind = i;
		// printf("\033[38;5;233munitializing philo %d\n", i + 1);
		if (pthread_create(&((*philo)[i].philo), NULL, philo_routine, &(*philo)[i]))
		{
			printf("\033[38;5;196an error occured while creating threads");
			return (1);
		}
		if (pthread_detach(((*philo)[i].philo)) != 0)
			return (1);
		// wait_die(*philo);
		i++;
		// if (pthread_detach(((*philo)[i].philo)))
		// 	return (0);
		usleep(800);
	}
	// return (check_die(*philo));
	return (0);
}

int	init_philo(t_philo **philo, t_info info)
{
	int	i;

	i = 0;
	(*philo) = malloc(info.count * sizeof(t_philo));
	if (!*philo)
		return (1);
	while (i < info.count)
	{
		if (i < info.count - 1)
			(*philo)[i].r_fork = &(*philo)[i + 1].l_fork;
		else
			(*philo)[i].r_fork = &(*philo)[0].l_fork;
		i++;
		(*philo)[i].r_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(&(*philo)[i].l_fork, NULL);
		pthread_mutex_init((*philo)[i].r_fork, NULL);
		pthread_mutex_init(&(*philo)[i].eat_time, NULL);
		(*philo)[i].count = info.count;
		(*philo)[i].t_eat = info.t_eat;
		(*philo)[i].t_die = info.t_die;
		(*philo)[i].t_sleep = info.t_sleep;
		// (*philo)[i].r_fork = malloc(sizeof(pthread_mutex_t));
		// pthread_mutex_init((*philo)[i].r_fork, NULL);
	}
	(*philo)->count = info.count;
	(*philo)->t_eat = info.t_eat;
	(*philo)->t_die = info.t_die;
	(*philo)->t_sleep = info.t_sleep;
	if (create_threads(philo))
		return (1);
	return (0);
}