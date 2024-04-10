/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:51:28 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/10 15:02:40 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	activity_logger(t_philo *philo, char *in)
{
	pthread_mutex_lock(&philo->core->write_lock);
	if (philo->core->living_state < 0)
		printf("%llu %i %s\n", (get_current_time())
			- (philo->core->start_time), philo->id, in);
	pthread_mutex_unlock(&philo->core->write_lock);
}

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

static void	eat(t_core *core, t_philo *philo)
{
	if (core->num_of_philos == 1)
		return ;
	pthread_mutex_lock(&philo->r_fork);
	activity_logger(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	activity_logger(philo, "has taken a fork");
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
	philo->last_meal = get_current_time();
	if (philo->wait == true)
		{
			ph_usleep(1);
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
