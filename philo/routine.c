#include "philo.h"

void	take_fork(t_philo	*p)
{
	pthread_mutex_lock(p->r_fork);
	printf("\033[38;5;46mphilo %d take right fork\n", p->ind);
	pthread_mutex_lock(&(p->l_fork));
	printf("\033[38;5;46mphilo %d take left fork\n", p->ind);
}

void sleep_philo(t_philo *p)
{
	printf("\033[38;5;46mphilo %d is sleeping\n", p->ind);
	wait_p(p->t_sleep);
	printf("\033[38;5;46mphilo %d is thinking\n", p->ind);
}

void	feed_philo(t_philo *p)
{
	pthread_mutex_lock(&(p->eat_time));
	printf("\033[38;5;46mphilo %d is eating\n", p->ind);
	wait_p(p->t_eat);
	p->last_eat = get_time();
	pthread_mutex_unlock(&(p->eat_time));
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(&p->l_fork);
}
