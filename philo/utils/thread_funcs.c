/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:51:28 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/28 18:05:55 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"


void	sleep(t_core *core, t_philo *philo)
{
	ph_usleep(core->time_to_sleep);
}

void	eat(t_core *core, t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = 1;
	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
	if (core->living_state == 1)
		printf("");
	ph_usleep(core->time_to_eat);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->meal_lock);
}

void	*ph_monitor(void *in)
{
	t_core	*core;
	int	i;

	core = (t_core *) in;
	while (core->living_state < 0)
	{
		i = -1;
		while (core->philos[++i])
			if (core->philos[i]->living_state < 0)
				core->living_state = core->philos[i]->id;
	}
	printf("philosopher %i has died of starvation\n", core->philos[i]->id);
	return (NULL);
}

void	*philo_brain(void *in)
{
	t_philo	*philo;

	philo = (t_philo *) in;
	while (philo->core->living_state < 0 && philo->living_state < 0)
	{
		if (philo->last_meal - get_current_time() > philo->core->time_to_die)
			philo->living_state = philo->id;
		else
		{
			eat(philo->core, philo);
			ph_usleep(philo->core->time_to_sleep);
		}
	}
	return (NULL);
}