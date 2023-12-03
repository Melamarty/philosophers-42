#include "philo_bonus.h"

void	print(char *msg, t_philo *philo)
{
	sem_wait (philo->info->msg_s);
	printf("%ld  %d		%s\n", get_time() - philo->info->start_time, philo->ind, msg);
	sem_post (philo->info->msg_s);
}
void	take_fork(t_philo	*p)
{
	sem_wait(p->info->fork);
	print("has taken a fork", p);
	sem_wait(p->info->fork);
	print("has taken a fork", p);
}

void sleep_philo(t_philo *p)
{
	print ("is sleeping", p);
	wait_p(p->info->t_sleep);
	print ("is thinking", p);
}

void	feed_philo(t_philo *p)
{
	// sem_wait(p->info->eat_s);
	print("is eating", p);
	// printf("deb ...\n");
	sem_wait(p->info->last_eat_s);
	++p->eat_c;
	p->last_eat = get_time();
	sem_post(p->info->last_eat_s);
	wait_p(p->info->t_eat);
	// printf("posting forks ...\n");
	sem_post(p->info->fork);
	sem_post(p->info->fork);
	// printf("fork posted ...\n");
}


// 0       1       has taken a fork
// 0       1       has taken a fork
// 0       1       is eating
// 0       2       has taken a fork
// 100     2       has taken a fork
// 100     3       has taken a fork
// 100     1       is sleeping
// 100     2       is eating
// 200     1       is thinking
// 200     2       is sleeping
// 200     3       has taken a fork
// 200     1       has taken a fork
// 200     3       is eating
// 300     2       is thinking
// 300     3       is sleeping
// 300     1       has taken a fork
// 300     2       has taken a fork
// 300     1       is eating