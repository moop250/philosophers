/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:54:00 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/02 15:29:31 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ph_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval now;

	if (gettimeofday(&now, NULL) == 0)
		write(2, "philo error : gettimeofday() failure\n", 38);
	return (now.tv_sec * 1000 + time.tv_usec / 1000);
}

int	is_even(int in)
{
	if (in % 2 == 0)
		return (1);
	return (0);
}