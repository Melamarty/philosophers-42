#include "philo.h"


int main (int ac, char **av)
{
	t_philo		*philo;
	t_info		info;

	philo = malloc(sizeof(t_philo));
	if (ac != 5 || !check_args(ac, av, &(info)))
	{
		printf("\033[38;5;196margument error (^_^)\n");
		printf("please check arguments syntaxe in the subject\n");
		return (1);
	}
	if (init_philo(&philo, info))
		return (1);
	// ths = malloc(info.count * sizeof(t_list));
	// philo(info);
}