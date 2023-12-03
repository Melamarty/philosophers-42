#include "philo_bonus.h"


int main (int ac, char **av)
{
	t_philo		*philos;
	t_info		*info;

	if (ac > 6 || check_args(ac, av))
	{
		printf("\033[38;5;196margument error (^_^)\n");
		printf("please check arguments syntaxe in the subject\n");
		return (1);
	}
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	init_info(ac, av, info);
	philos = malloc(sizeof(t_philo) * info->count);
	if (!philos)
		return (free (philos), 1);
	if (init_philos(philos, info))
		return (1);
	ft_destroy(philos->info);
	free (philos);
	return (0);
}