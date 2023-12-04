#include "philo.h"

void	print(char *msg, t_philo *philo)
{
	if (philo->info->meals && philo->eat_c == philo->info->meals)
		return ;
	pthread_mutex_lock (&philo->info->fin_m);
	if (philo->info->fin)
	{
		pthread_mutex_unlock (&philo->info->fin_m);
		return ;
	}
	pthread_mutex_lock (&philo->info->msg_s);
	printf("%ld        %d		%s\n", get_time() - philo->info->start_time, philo->ind, msg);
	pthread_mutex_unlock(&philo->info->msg_s);
	pthread_mutex_unlock (&philo->info->fin_m);
}

void	take_fork(t_philo	*p)
{
	pthread_mutex_lock(&p->l_fork);
	print("has taken left fork", p);
	if (p->info->count == 1)
	{
		wait_p(p->info->t_die);
		pthread_mutex_unlock(&p->l_fork);
		return ;
	}
	pthread_mutex_lock(p->r_fork);
	print("has taken right fork", p);
}

void sleep_philo(t_philo *p)
{
	print("is sleeping", p);
	wait_p(p->info->t_sleep);
	print("is thinking", p);
}

void	feed_philo(t_philo *p)
{
	print("is eating", p);
	++p->eat_c;
	pthread_mutex_lock(&p->eat_time);
	p->last_eat = get_time();
	pthread_mutex_unlock(&p->eat_time);
	wait_p(p->info->t_eat);
	pthread_mutex_lock(&p->info->meals_time);
	if (p->eat_c == p->info->meals)
		++p->info->m_counter;
	pthread_mutex_unlock(&p->info->meals_time);
	pthread_mutex_unlock(&p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}
