/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:18 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/11 17:30:27 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_philos(t_core *core)
{
	int	i;

	i = -1;
	while (core->philos[++i])
	{
		pthread_mutex_destroy(&core->philos[i]->r_fork);
		pthread_mutex_destroy(&core->philos[i]->meal_lock);
		pthread_mutex_destroy(&core->philos[i]->hunger_lock);
		free(core->philos[i]);
	}
	free(core->philos);
}

static void	free_core(t_core *core)
{
	if (core->philos)
	{
		free_philos(core);
		pthread_mutex_destroy(&core->write_lock);
		pthread_mutex_destroy(&core->living_lock);
	}
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
	core->finished = true;
	pthread_join(monitor, NULL);
	free_core(core);
	return (0);
}
