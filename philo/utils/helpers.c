/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:54:00 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/09 18:29:53 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ph_usleep(long long microseconds)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < microseconds)
		usleep(500);
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000000 + now.tv_usec);
}

int	is_even(int in)
{
	if (in % 2 == 0)
		return (1);
	return (0);
}
