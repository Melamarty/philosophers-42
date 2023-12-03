#include "philo.h"

void	print(char *msg, t_philo *philo)
{
	pthread_mutex_lock (&philo->info->msg_s);
	printf("%ld  %d		%s\n", get_time() - philo->info->start_time, philo->ind, msg);
	pthread_mutex_unlock(&philo->info->msg_s);
}

void	take_fork(t_philo	*p)
{
	pthread_mutex_lock(p->r_fork);
	print("has taken right fork", p);
	// printf("\033[38;5;46mphilo %d take right fork\n", p->ind);
	if (p->info->count == 1)
		return (wait_p(p->info->t_die));
	pthread_mutex_lock(&(p->l_fork));
	print("has taken left fork", p);
	// printf("\033[38;5;46mphilo %d take left fork\n", p->ind);
}

void sleep_philo(t_philo *p)
{
	print("is sleeping", p);
	// printf("\033[38;5;46mphilo %d is sleeping\n", p->ind);
	wait_p(p->info->t_sleep);
	print("is thinking", p);
	// printf("\033[38;5;46mphilo %d is thinking\n", p->ind);
}

void	feed_philo(t_philo *p)
{
	pthread_mutex_lock(&p->eat_time);
	print("is eating", p);
	// printf("\033[38;5;46mphilo %d is eating\n", p->ind);
	p->last_eat = get_time();
	++p->eat_c;
	// printf("eat_c %d meals %d\n", p->eat_c, p->info->meals);
	if (p->eat_c >= p->info->meals)
		(p->info->m_counter++) && (p->eat_c = 0);
	// printf("eat_c %d m_counter %d\n", p->eat_c, p->info->m_counter);
	pthread_mutex_unlock(&p->eat_time);
	wait_p(p->info->t_eat);
	// printf("finished\n");
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(&p->l_fork);
}
