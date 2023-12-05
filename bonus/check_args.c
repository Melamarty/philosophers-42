/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:47:18 by mel-amar          #+#    #+#             */
/*   Updated: 2023/12/05 05:47:19 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

int	is_nb(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int	is_not_nb(char *nb)
{
	if (*nb == '-' || *nb == '+')
		nb++;
	if (*nb > '9' || *nb < '0')
		return (1);
	while (*nb && *nb != ' ')
	{
		if (*nb > '9' || *nb < '0')
			return (1);
		nb++;
	}
	return (0);
}

int	check_args(char **nbs, int ac)
{
	int	i;

	i = 1;
	if (ac > 6 || ac < 5)
		return (1);
	while (i < ac)
	{
		if (is_not_nb(nbs[i]))
			return (1);
		if (ft_atoi(nbs[i]) > INT_MAX || ft_atoi(nbs[i]) < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}
