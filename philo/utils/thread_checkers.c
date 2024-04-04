/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_checkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:09:01 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/04 14:19:56 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	checkdeath(t_philo *philo, t_core *core)
{
	int	status;

	pthread_mutex_lock(&core->death_lock);
	status = core->living_state;
	pthread_mutex_unlock(&core->death_lock);
	if (status < 0)
		return (0);
	return (1);
}

int	checkhunger(t_philo *philo, t_core *core)
{
	if (philo->meals_eaten >= core->eat_limit)
	{
		philo->is_done = true;
		return (0);
	}
	return (1);
}
