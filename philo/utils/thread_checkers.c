/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_checkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:09:01 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/11 17:31:09 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	checkdeath(t_core *core)
{
	int	status;

	pthread_mutex_lock(&core->living_lock);
	status = core->living_state;
	pthread_mutex_unlock(&core->living_lock);
	if (status >= 0)
		return (1);
	return (0);
}

int	checkhunger(t_philo *philo, t_core *core)
{
	pthread_mutex_lock(&philo->hunger_lock);
	if (philo->meals_eaten > core->eat_limit && core->eat_limit != 0)
	{
		philo->is_done = true;
		pthread_mutex_unlock(&philo->hunger_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->hunger_lock);
	return (1);
}
