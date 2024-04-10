/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:51:28 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/10 16:29:50 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	think(t_philo *philo)
{
	activity_logger(philo, "is thinking");
	ph_usleep(1);
	philo->has_thought = true;
}

static void	ph_sleep(t_core *core, t_philo *philo)
{
	activity_logger(philo, "is sleeping");
	if (!checkdeath(core))
		ph_usleep(core->time_to_sleep);
	philo->has_eaten = false;
	philo->has_thought = false;
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
		philo->last_meal = get_current_time();
		if (core->eat_limit > 0)
			philo->meals_eaten++;
	}
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*philo_brain(void *in)
{
	t_philo	*philo;

	philo = (t_philo *) in;
	while (!philo->core->initialized)
		;
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
		if (!philo->has_thought)
			think(philo);
		else if (!philo->has_eaten)
			eat(philo->core, philo);
		else
			ph_sleep(philo->core, philo);
	}
	return (0);
}
