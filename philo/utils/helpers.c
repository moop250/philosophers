/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:54:00 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/10 16:24:19 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ph_usleep(long long miliseconds)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < miliseconds)
		usleep(500);
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

int	is_even(int in)
{
	if (in % 2 == 0)
		return (1);
	return (0);
}

void	activity_logger(t_philo *philo, char *in)
{
	pthread_mutex_lock(&philo->core->write_lock);
	if (philo->core->living_state < 0)
		printf("%llu %i %s\n", (get_current_time())
			- (philo->core->start_time), philo->id, in);
	pthread_mutex_unlock(&philo->core->write_lock);
}
