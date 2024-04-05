/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:18 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/06 00:47:23 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_philos(t_core *core)
{
	int	i;

	i = -1;
	while (core->philos[++i])
	{
		if (&core->philos[i]->r_fork)
			pthread_mutex_destroy(&core->philos[i]->r_fork);
		if (&core->philos[i]->meal_lock)
			pthread_mutex_destroy(&core->philos[i]->meal_lock);
		if (&core->philos[i]->hunger_lock)
			pthread_mutex_destroy(&core->philos[i]->hunger_lock);
		if (&core->philos[i]->lml)
			pthread_mutex_destroy(&core->philos[i]->lml);
		free(core->philos[i]);
	}
	free(core->philos);
}

static void	free_core(t_core *core)
{
	if (core->philos)
		free_philos(core);
	if (&core->death_lock)
		pthread_mutex_destroy(&core->death_lock);
	if (&core->write_lock)
		pthread_mutex_destroy(&core->write_lock);
	if (&core->monitor_lock)
		pthread_mutex_destroy(&core->monitor_lock);
	free(core);
}

int	main(int ac, char **av)
{
	t_core		*core;
	int			i;
	pthread_t	monitor;

	if (checker(ac, av))
		return (1);
	core = malloc(sizeof(t_core));
	if (!core)
		return (2);
	if (fillcore(core, av))
	{
		free_core(core);
		return (3);
	}
	core->finished = false;
	pthread_create(&monitor, NULL, &ph_monitor, (void *)core);
	i = -1;
	while (core->philos[++i])
		pthread_join(core->philos[i]->thread, NULL);
	pthread_mutex_lock(&core->monitor_lock);
	core->finished = true;
	pthread_mutex_unlock(&core->monitor_lock);
	pthread_join(monitor, NULL);
	free_core(core);
	return (0);
}
