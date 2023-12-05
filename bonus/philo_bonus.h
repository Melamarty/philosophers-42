/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:48:03 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/05 05:48:04 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <libc.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_info
{
	pthread_t	monitor;
	sem_t		*fin;
	sem_t		*fork;
	sem_t		*die_s;
	sem_t		*msg;
	int			count;
	long int	t_eat;
	long int	t_sleep;
	long int	t_die;
	long int	meals;
	long int	start;
}				t_info;

typedef struct s_philo
{
	pid_t		pid_philo;
	sem_t		*last_eat_s;
	t_info		*info;
	int			ind;
	int			meals_count;
	long		last_eat;
}				t_philo;

long			ft_atoi(const char *str);
int				create_thread_check_try(t_philo *philos);
size_t			ft_strlen(const char *s);
void			*check_meals(void *args);
int				ft_check_error(int ac, char **av);
void			*check_die(void *args);
int				take_fork(t_philo *philo);
int				feed_philo(t_philo *philo);
void			sleep_philo(t_philo *philo);
long			get_time(void);
void			wait_philo(long time);
int				create_philos(t_philo *philos);
int				init_info(t_info *info, char **av, int ac);
int				init_philo(t_philo *philos, t_info *info);
void			print(char *str, t_philo *philo, int flag);
void			philo_routine(t_philo *philo);
// long			ft_get_time_ms(void);
void			close_sems(t_philo *philos);
int				check_args(char **nbs, int ac);

#endif