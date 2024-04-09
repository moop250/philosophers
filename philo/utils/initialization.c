/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:59:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/09 18:19:32 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	init_philos(t_core *core, int i)
{
	core->philos[i] = malloc(sizeof(t_philo));
	if (!core->philos[i])
		return (1);
	core->philos[i]->id = i;
	if (pthread_mutex_init(&core->philos[i]->hunger_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&core->philos[i]->r_fork, NULL) != 0)
		return (1);
	if (i == core->num_of_philos - 1)
		core->philos[0]->l_fork = core->philos[i]->r_fork;
	else if (i != 0)
		core->philos[i]->l_fork = core->philos[i - 1]->r_fork;
	core->philos[i]->core = core;
	core->philos[i]->living_state = -1;
	core->philos[i]->has_thought = false;
	core->philos[i]->has_eaten = false;
	if (is_even(i))
		core->philos[i]->wait = false;
	else
		core->philos[i]->wait = true;
	core->philos[i]->is_done = false;
	core->philos[i]->meals_eaten = 0;
	return (0);
}

static int	init_threads(t_core *core)
{
	int	i;
	size_t	start_time;

	i = -1;
	core->initialized = false;
	start_time = get_current_time();
	core->start_time = start_time;
	while (core->philos[++i])
	{
		core->philos[i]->last_meal = start_time;
		pthread_create(&core->philos[i]->thread, NULL, &philo_brain,
			(void *)core->philos[i]);
	}
	core->initialized = true;
	return (0);
}

int	fillcore(t_core *core, char **av)
{
	int	i;

	core->num_of_philos = ph_atoi(av[1]);
	core->time_to_die = ph_atoi(av[2]) * 1000;
	core->time_to_eat = ph_atoi(av[3]) * 1000;
	core->time_to_sleep = ph_atoi(av[4]) * 1000;
	core->eat_limit = 0;
	if (av[5])
		core->eat_limit = ph_atoi(av[5]);
	core->living_state = -1;
	core->philos = malloc((core->num_of_philos + 1) * sizeof(t_philo *));
	if (!core->philos)
		return (1);
	if (pthread_mutex_init(&core->write_lock, NULL) != 0)
		return (1);
	i = -1;
/* 	init_forks(core); */
	while (++i < core->num_of_philos)
		if (init_philos(core, i))
			return (1);
	core->philos[i] = NULL;
	if (init_threads(core))
		return (1);
	return (0);
}
