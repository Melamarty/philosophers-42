#include "philo.h"

int	check_die(t_philo *p)
{
	int i;
	while (1)
	{
		i = -1;
		while (++i < p->info->count)
		{
			pthread_mutex_lock(&p->info->meals_time);
			// printf("m_counter : %d\n", p->info->m_counter);
			if (p->info->m_counter == p->info->count)
			{
				p->info->fin = 1;
				pthread_mutex_unlock(&p->info->meals_time);
				// printf("finished\n");
				return (0);
			}
			pthread_mutex_unlock(&p->info->meals_time);
			pthread_mutex_lock(&p[i].eat_time);
			if (get_time() - p[i].last_eat > p->info->t_die)
			{
				pthread_mutex_unlock(&p[i].eat_time);
				print("is_die", &p[i]);
				return (1);
			}
			pthread_mutex_unlock(&p[i].eat_time);
			usleep(200);
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->eat_time);
	p->last_eat = get_time();
	pthread_mutex_unlock(&p->eat_time);
	while (1)
	{
		take_fork(p);
		if (p->info->count == 1)
			return (NULL);
		feed_philo(p);
		sleep_philo(p);
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
		if (pthread_create(&(philos[i].philo), NULL, philo_routine, &philos[i]))
			return (1);
		if (pthread_detach((philos)[i].philo))
			return (1);
		usleep(200);
	}
	return (check_die(philos));
	return (0);
}

int	init_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	info->start_time = get_time();
	pthread_mutex_init(&info->meals_time, NULL);
	pthread_mutex_init(&info->fin_m, NULL);
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