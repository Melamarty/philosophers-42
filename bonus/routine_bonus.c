#include "philo_bonus.h"

void	philo_routine(t_philo *philo)
{
	philo->last_eat = get_time();
	if (pthread_create(&philo->info->monitor, NULL, check_die, philo) != 0)
		return ;
	if (pthread_detach(philo->info->monitor) != 0)
		return ;
	while (1)
	{
		if (take_fork(philo))
			exit(0);
		feed_philo(philo);
		sleep_philo(philo);
	}
	return ;
}


void	wait_philo(long ms)
{
	long	curr;

	curr = get_time();
	while (get_time() < curr + ms)
		usleep(100);
}

int	take_fork(t_philo *philo)
{
	sem_wait(philo->info->fork);
	print("has taken a fork", philo, 0);
	if (philo->info->count == 1)
	{
		sem_post(philo->info->fork);
		wait_philo(philo->info->t_die);
		print("die", philo, 1);
		return (1);
	}
	sem_wait(philo->info->fork);
	print("has taken a fork", philo, 0);
	return (0);
}

void	sleep_philo(t_philo *philo)
{
	print("is sleeping", philo, 0);
	wait_philo(philo->info->t_sleep);
	print("is thinking", philo, 0);
}

int	feed_philo(t_philo *philo)
{
	print("is eating", philo, 0);
	sem_wait(philo->last_eat_s);
	philo->eat_c++;
	philo->last_eat = get_time();
	sem_post(philo->last_eat_s);
	wait_philo(philo->info->t_eat);
	sem_post(philo->info->fork);
	sem_post(philo->info->fork);
	if (philo->eat_c == philo->info->meals)
		sem_post(philo->info->fin);
	return (0);
}

void	print(char *str, t_philo *philo, int flag)
{
	if (flag == 1 || flag == 0)
	{
		sem_wait(philo->info->msg_s);
		printf("%ld\t%d\t%s\n", get_time() - philo->info->start_time,
			philo->ind, str);
		if (flag == 1)
		{
			sem_post(philo->last_eat_s);
			sem_post(philo->info->die_s);
			close_sem(philo);
		}
		else
			sem_post(philo->info->msg_s);
	}
}

// void	print(char *msg, t_philo *philo)
// {
// 	// if (philo->info->stop)
// 	// 	return ;
// 	sem_wait (philo->info->msg_s);
// 	printf("%ld  %d		%s\n", get_time() - philo->info->start_time, philo->ind, msg);
// 	// if (!philo->info->stop)
// 	sem_post (philo->info->msg_s);
// 	// else
// 	// {
// 	// 	sem_post(philo->last_eat_s);
// 	// 	sem_post(philo->info->die_s);
// 	// 	ft_destroy(philo);
// 	// }
// }

// void	take_fork(t_philo	*p)
// {
// 	sem_wait(p->info->fork);
// 	print("has taken a fork", p);
// 	sem_wait(p->info->fork);
// 	print("has taken a fork", p);
// }

// void sleep_philo(t_philo *p)
// {
// 	print ("is sleeping", p);
// 	wait_p(p->info->t_sleep);
// 	print ("is thinking", p);
// }

// void	feed_philo(t_philo *p)
// {
// 	// sem_wait(p->info->eat_s);
// 	print("is eating", p);
// 	// printf("deb ...\n");
// 	sem_wait(p->last_eat_s);
// 	++p->eat_c;
// 	p->last_eat = get_time();
// 	sem_post(p->last_eat_s);
// 	wait_p(p->info->t_eat);
// 	// printf("posting forks ...\n");
// 	sem_post(p->info->fork);
// 	sem_post(p->info->fork);
// 	// printf("fork posted ...\n");
// }