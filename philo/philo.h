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
	int 			count;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meals;
	pthread_mutex_t	meals_time;
	pthread_mutex_t	msg_s;
	pthread_mutex_t	last_time_s;
	pthread_mutex_t	fin_m;
	long int		start_time;
	int				m_counter;
	int				fin;
} t_info;

typedef struct s_list
{
	pthread_t		philo;
	t_info			*info;
	pthread_mutex_t eat_time;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	int				ind;
	long int		last_eat;
	int				eat_c;
} t_philo;

long	ft_atoi(const char *str);
int 	check_args (int ac, char **av, t_info *info);
int		init_philo(t_philo *philo, t_info *info);
void	wait_p(int	time);
void	take_fork(t_philo	*p);
void 	sleep_philo(t_philo *p);
void	feed_philo(t_philo *p);
long 	get_time();
void	print(char *msg, t_philo *philo);

#endif