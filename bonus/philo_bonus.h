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
	sem_t	*die_s;
	sem_t	*fin;
	int		meals;
	int count;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	long int		start_time;
	pthread_t	monitor;
	int		stop;
} t_info;

typedef struct s_list
{
	sem_t			*last_eat_s;
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
// void	print(char *msg, t_philo *philo);
// void	wait_p(int	time);
// void 	sleep_philo(t_philo *p);
// void	feed_philo(t_philo *p);
int		ft_destroy(t_philo *philo);
void	ft_kill(t_philo *philos);


void	philo_routine(t_philo *philo);
void	wait_philo(long ms);
int		take_fork(t_philo *philo);
void	sleep_philo(t_philo *philo);
int		feed_philo(t_philo *philo);
void	print(char *str, t_philo *philo, int flag);
void	*check_die(void *args);
void	*check_meals(void *args);
void	close_sem(t_philo *philos);
long	get_time(void);

#endif