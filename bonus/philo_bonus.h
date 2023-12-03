#ifndef PHILPSOPHER_H
# define PHILPSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <sys/time.h>
#include <semaphore.h>

typedef struct s_info
{
	sem_t	*fork;
	sem_t	*msg_s;
	sem_t	*eat_s;
	sem_t	*last_eat_s;
	sem_t	*die_s;
	sem_t	*fin;
	int		meals;
	int count;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	long int		start_time;
	int		stop;
} t_info;

typedef struct s_list
{
	pid_t			philo;
	t_info			*info;
	pthread_t		monitor;
	int				eat_c;
	int				ind;
	long int		last_eat;
} t_philo;

long	ft_atoi(const char *str);
int 	check_args (int ac, char **av);
int		init_info(int ac, char **av, t_info *info);
int		init_philos(t_philo *philos, t_info *info);
void	print(char *msg, t_philo *philo);
void	wait_p(int	time);
void	take_fork(t_philo	*p);
void 	sleep_philo(t_philo *p);
void	feed_philo(t_philo *p);
long 	get_time();
int		ft_destroy(t_info *info);

#endif