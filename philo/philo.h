#ifndef PHILPSOPHER_H
# define PHILPSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>

typedef struct s_info
{
	int count;
	int	t_die;
	int	t_eat;
	int	t_sleep;
} t_info;

typedef struct s_list
{
	pthread_t		philo;
	pthread_mutex_t eat_time;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	int				is_die;
	int				ind;
	int				last_eat;
	int count;
	int	t_die;
	int	t_eat;
	int	t_sleep;
} t_philo;

long	ft_atoi(const char *str);
int 	check_args (int ac, char **av, t_info *info);
int		init_philo(t_philo **philo, t_info info);
void	wait_p(int	time);
void	take_fork(t_philo	*p);
void 	sleep_philo(t_philo *p);
void	feed_philo(t_philo *p);
long 	get_time();

#endif