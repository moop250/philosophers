/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:11:15 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/05 19:32:07 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	kill_philos(t_core *core, t_philo *philo)
{
	pthread_mutex_lock(&core->death_lock);
	pthread_mutex_lock(&core->write_lock);
	core->living_state = philo->id;
	printf("%zu %i has died\n", get_current_time() - philo->start_time,
		philo->id);
	pthread_mutex_unlock(&core->death_lock);
	pthread_mutex_unlock(&core->write_lock);
}

static int	check_starving(t_philo *philo)
{
	if (get_current_time() - philo->last_meal <= philo->core->time_to_die)
		return (1);
	return (0);
}

static int	check_done(t_philo *philo)
{
	if (philo->is_done == true)
		return (1);
	return (0);
}

void	*ph_monitor(void *in)
{
	t_core	*core;
	int		i;

	core = (t_core *)in;
	while (true)
	{
		if (core->living_state >= 0)
			break ;
		i = -1;
		while (core->philos[++i])
		{
			if (!checkdeath(core))
				return (0);
			if (!check_done(core->philos[i]) && check_starving(core->philos[i]))
				kill_philos(core, core->philos[i]);
		}
		ph_usleep(1);
	}
	return (0);
}