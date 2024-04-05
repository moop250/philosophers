/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:49:48 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/05 14:18:21 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	basic_checker(int ac, char *av)
{
	if (ac < 5)
	{
		write(2, "philo error: not enough args\n", 30);
		return (1);
	}
	else if (ac > 6)
	{
		write(2, "philo error: too many args\n", 28);
		return (1);
	}
	else if(atoi(av) > 200)
	{
		write(2, "philo error: too many philosophers\n", 36);
		return (1);
	}
	return (0);
}

int	checker(int ac, char **av)
{
	int	i;
	int	a;
	if (basic_checker(ac, av[1]) == 1)
		return (1);
	a = 0;
	while (av[++a])
	{
		i = -1;
		while (av[a][++i])
		{
			if (!isdigit(av[a][i]))
			{
				write(2, "philo error: non numeric argument\n", 35);
				return (1);
			}
			if (av[a][0] == '0' && av[a][1] == '\0' && a != 5)
			{
				write(2, "philo error: number smaller than 1 entered\n", 44);
				return (1);
			}
		}
	}
	return (0);
}