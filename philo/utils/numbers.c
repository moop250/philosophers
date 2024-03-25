/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:30:04 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/25 14:17:20 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static int	ret(const char *str, int i, int n)
{
	unsigned int	o;

	o = 0;
	while (isdigit(str[i]) == 1)
	{
		o = o * 10 + (str[i] - '0');
		i++;
	}
	return ((int)o * n);
}

int	ph_atoi(const char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	if (!str[0])
		return (0);
	while (isspace(str[i]) == 1)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (isdigit(str[i + 1]) != 1)
			return (0);
		else if (str[i] == '-')
			n *= -1;
		i++;
	}
	return (ret(str, i, n));
}
