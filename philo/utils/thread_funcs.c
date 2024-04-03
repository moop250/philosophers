/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:51:28 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/03 17:20:42 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	activity_logger(t_philo *philo, char *in)
{
	pthreaf_mutex_lock(&philo->core->write_lock);
	pthread_mutex_lock(&philo->core->death_lock);
		if (philo->core->living_state < 0)
			printf("%zu %i %s\n", get_current_time() - philo->start_time, in);
	pthread_mutex_unlock(&philo->core->death_lock);
	pthread_mutex_unlock(&philo->core->write_lock);
}

static void	think(t_philo *philo)
{
	activity_logger(philo, "is thinking");
	philo->has_thought = true;
}

static void	sleep(t_core *core, t_philo *philo)
{
	activity_logger(philo, "is sleeping");
	if (!checkdeath(philo, core))
		ph_usleep(core->time_to_sleep);
	philo->has_eaten = false;
	philo->has_thought = false;
}

static void	eat(t_core *core, t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	activity_logger(philo, "has taken a fork");
	pthread_mutex_lock(&philo->l_fork);
	activity_logger(philo, "has taken a fork");
	activity_logger(philo, "is eating");
	if (!checkdeath(philo, core))
	{
		ph_usleep(core->time_to_eat);
		philo->has_eaten = true;
		philo->last_meal = get_current_time();
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
}

void	*philo_brain(void *in)
{
	t_philo	*philo;

	philo = (t_philo *) in;
	while (true)
	{
		if (!checkhunger(philo, philo->core))
			break ;
		if (philo->wait == true)
		{
			ph_usleep(5);
			philo->wait = false;
		}
		if (checkdeath(philo, philo->core))
			break ;
		if (!philo->has_thought)
			think(philo);
		else if (!philo->has_eaten)
			eat(philo->core, philo);
		else
			ph_sleep(philo->core->time_to_sleep);
	}
	return (NULL);
}