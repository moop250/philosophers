/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:54:00 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/12 16:01:28 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long long	get_current_time(int ms_us)
{
	struct timeval	time;
	long			time_ret;

	time_ret = 0;
	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday error", 19);
	if (ms_us == 1)
		time_ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	else if (ms_us == 2)
		time_ret = time.tv_sec * 1000000 + time.tv_usec;
	return (time_ret);
}

void	ph_usleep(long usec)
{
	long	start;
	long	diff;
	long	remaining;

	start = get_current_time(2);
	while (get_current_time(2) - start < usec)
	{
		diff = get_current_time(2) - start;
		remaining = usec - diff;
		if (remaining > 10000)
			usleep(remaining / 2);
		else
			while (get_current_time(2) - start < usec)
				;
	}
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
		printf("%llu %i %s\n", (get_current_time(1))
			- (philo->core->start_time / 1000), philo->id, in);
	pthread_mutex_unlock(&philo->core->write_lock);
}
