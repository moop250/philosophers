/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:29 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/25 18:25:02 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Includes

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdatomic.h>

// Structs

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				*living_state;
	size_t			last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}				t_philo;

typedef struct s_core
{
	int			num_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			eat_limit;
	atomic_bool	living_state;
	t_philo		**philos;
}				t_core;

// Custom Functions

int		checker(int ac, char **av);
int		ph_atoi(const char *str)
int		isdigit(int c);

#endif