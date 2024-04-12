/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:11:15 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/12 16:02:41 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	kill_philos(t_core *core, t_philo *philo)
{
	pthread_mutex_lock(&core->write_lock);
	pthread_mutex_lock(&core->living_lock);
	if (core->living_state < 0)
		printf("%llu %i has died\n", (get_current_time(1))
			- (core->start_time) / 1000, philo->id);
	core->living_state = philo->id;
	pthread_mutex_unlock(&core->living_lock);
	pthread_mutex_unlock(&core->write_lock);
}

static int	check_starving(t_philo *philo)
{
	if (get_current_time(2) - philo->last_meal <= philo->core->time_to_die
		|| philo->wait == true)
		return (0);
	return (1);
}

static int	check_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->hunger_lock);
	if (philo->is_done == true)
	{
		pthread_mutex_unlock(&philo->hunger_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->hunger_lock);
	return (0);
}

static int	checking(t_core *core)
{
	int		i;

	i = -1;
	while (core->philos[++i])
	{
		if (checkdeath(core))
			return (0);
		if (!check_done(core->philos[i]) && check_starving(core->philos[i]))
			kill_philos(core, core->philos[i]);
	}
	return (1);
}

void	*ph_monitor(void *in)
{
	t_core	*core;

	core = (t_core *)in;
	while (true)
	{
		if (core->living_state >= 0)
			break ;
		if (core->finished == true)
			break ;
		if (!checking(core))
			return (0);
		ph_usleep(1);
	}
	return (0);
}
