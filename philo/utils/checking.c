/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:49:48 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/21 17:13:49 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_error(char *error)
{
	printf("philo error: %s\n", error);
}

int	basic_checker(int ac, char *av)
{
	if (ac < 6)
	{
		print_error("not enough args");
		return (1);
	}
	else if (ac > 7)
	{
		print_error("too many args");
	return (1);
	}
	else if(atoi(av) > 200)
	{
		print_error("too many philosophers");
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
				print_error("non numeric argument");
				return (1);
			}
			if (av[a][0] == '0' && av[a][1] == '\0' && a != 6)
			{
				print_error("number smaller than 1 entered");
				return (1);
			}
		}
	}
	return (0);
}