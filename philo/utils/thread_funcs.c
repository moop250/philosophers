/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:51:28 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/27 17:19:38 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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
	while (philo->core->living_state = 1)
	{
		
	}
	return (NULL);
}