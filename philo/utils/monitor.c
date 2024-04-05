/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:11:15 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/05 11:39:56 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	kill_philos(t_core *core, t_philo *philo)
{
	
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
			if (!checkdeath(core->philos[i], core))
				return (0);
			if (!check_done(core->philos[i]) && check_straving(core->philos[i]))
				kill_philos(core, core->philos[i]);
		}
		ph_usleep(1);
	}
	return (0);
}