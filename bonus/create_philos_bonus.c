#include "philo_bonus.h"

int	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	// printf("%d\n", (*philo)->count);
	while (i < (*philo)->count)
	{
		(*philo)[i].ind = i;
		// printf("\033[38;5;233munitializing philo %d\n", i + 1);
		if (pthread_create(&((*philo)[i].philo), NULL, philo_routine, &(*philo)[i]))
		{
			printf("\033[38;5;196an error occured while creating threads");
			return (1);
		}
		if (pthread_detach(((*philo)[i].philo)) != 0)
			return (1);
		// wait_die(*philo);
		i++;
		// if (pthread_detach(((*philo)[i].philo)))
		// 	return (0);
		usleep(800);
	}
	// return (check_die(*philo));
	return (0);
}