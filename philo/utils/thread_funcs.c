/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:51:28 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/12 16:02:29 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	think(t_philo *philo)
{
	activity_logger(philo, "is thinking");
	ph_usleep(philo->core->time_to_think);
	philo->has_eaten = false;
	philo->has_slept = false;
}

static void	ph_sleep(t_core *core, t_philo *philo)
{
	activity_logger(philo, "is sleeping");
	if (!checkdeath(core))
		ph_usleep(core->time_to_sleep);
	philo->has_slept = true;
}

static void	eat_lock(t_philo *philo, int in)
{
	if (in == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		activity_logger(philo, "has taken a fork");
		pthread_mutex_lock(&philo->r_fork);
		activity_logger(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork);
		activity_logger(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		activity_logger(philo, "has taken a fork");
	}
}

static void	eat(t_core *core, t_philo *philo)
{
	if (core->num_of_philos == 1)
		return ;
	if (philo->id != 0)
		eat_lock(philo, 0);
	else
		eat_lock(philo, 1);
	activity_logger(philo, "is eating");
	if (!checkdeath(core))
	{
		ph_usleep(core->time_to_eat);
		philo->has_eaten = true;
		philo->last_meal = get_current_time(2);
		if (core->eat_limit > 0)
			philo->meals_eaten++;
	}
	if (philo->id != 0)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
}

void	*philo_brain(void *in)
{
	t_philo	*philo;

	philo = (t_philo *) in;
	if (philo->wait == true)
	{
		ph_usleep(5);
		philo->wait = false;
	}
	while (true)
	{
		if (!checkhunger(philo, philo->core))
			break ;
		if (checkdeath(philo->core))
			break ;
		if (!philo->has_eaten)
			eat(philo->core, philo);
		else if (!philo->has_slept)
			ph_sleep(philo->core, philo);
		else
			think(philo);
	}
	return (0);
}
