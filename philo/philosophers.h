/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:29 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/02 18:47:09 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Includes

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

// Structs

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				has_eaten;
	int				has_thought;
	size_t			last_meal;
	size_t			start_time;
	int				meals_eaten;
	int				living_state;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	meal_lock;
	t_core			*core;
}					t_philo;

typedef struct s_core
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				eat_limit;
	int				living_state;
	t_philo			**philos;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	write_lock;
}					t_core;

// Custom Functions

int		checker(int ac, char **av);
int		ph_atoi(const char *str);
int		isdigit(int c);
void	*philo_brain(void *in);
size_t	get_current_time(void);
int		ph_usleep(size_t milliseconds);
int		is_even(int in);
int		checkdeath(t_philo *philo, t_core *core);
int		checkhunger(t_philo *philo, t_core *core):

#endif