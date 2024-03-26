/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:18 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/26 17:58:46 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_core(t_core *core)
{
	int	i;

	i = -1;
	if (core->philos)
	{
		while (core->philos[++i])
		{
			if (core->philos[i]->r_fork)
				pthread_mutex_destroy(core->philos[i]->r_fork)
			free(core->philos[i]);
		}
		free(core->philos);
	}
	free(core);
}

int	init_threads(t_core *core, int i)
{
	core->philos[i] = malloc(sizeof(t_philo));
	if (!core->philos[i])
		return (1);
	core->philos[i]->id = i;
	if (pthread_mutex_init(&core->philos[i]->r_fork, NULL) != 0)
		return (1);
	if (i != 0)
		core->philos[i]->l_fork = core->philos[i - 1]->r_fork;
	else if (i == core->num_of_philos - 1)
		core->philos[0]->l_fork = core->philos[i]->r_fork;
	core->philos[i]->core = core;
	core->philos[i]->living_state = -1;
	pthread_create(&core->philos[i]->thread, NULL, &philo_brain,
		(void *) &core->philos[i]);
	return (0);
}

int	fillcore(t_core *core, char **av)
{
	int	i;

	i = -1;
	core->num_of_philos = ph_atoi(av[1]);
	core->time_to_die = ph_atoi(av[2]);
	core->time_to_eat = ph_atoi(av[3]);
	core->time_to_sleep = ph_atoi(av[4]);
	if (av[5])
		core->eat_limit = ph_atoi(av[5]);
	core->living_state = -1;
	core->philos = malloc((core->num_of_philos + 1) * sizeof(t_philo *));
	if (!core->philos)
		return (1);
	while (++i < core->num_of_philos)
		if (init_threads(core, i) == 1)
			return (1);
	core->philos[i] = NULL;
	return (0);
}

int	main(int ac, char **av)
{
	t_core		*core;
	int			i;
	pthread_t	monitor;

	if (checker(ac, av) == 1)
		return (1);
	core = malloc(sizeof(t_core));
	if (!core)
		return (2);
	if (fillcore(core, av))
		free_core(core);
	pthread_create(monitor, NULL, &ph_monitor, (void *) &core);
	pthread_join(monitor, NULL)
	i = -1;
	while (core->philos[++i])
		pthread_join(core->philos[i]->thread, NULL);
	free_core(core);
	return (0);
}