/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:46:44 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/05 05:46:47 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free(t_info *info, t_philo *ph)
{
	free(info);
	free(ph);
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_info	*info;

	if (check_args(av, ac))
	{
		printf("arguments error\n");
		return (0);
	}
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	if (init_info(info, av, ac))
		return (free(info), 1);
	philos = malloc(sizeof(t_philo) * info->count);
	if (!philos)
		return (free(info), 1);
	if (init_philo(philos, info))
		return (ft_free(info, philos), 1);
	if (create_philos(philos))
		return (ft_free(info, philos), 1);
	ft_free(info, philos);
	return (0);
}
