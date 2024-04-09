/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:29 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/09 18:31:19 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Includes

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdatomic.h>

// Structs

/* Forward declarations */
typedef struct s_philo	t_philo;
typedef struct s_core	t_core;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				has_eaten;
	int				has_thought;
	atomic_size_t	last_meal;
	int				meals_eaten;
	int				living_state;
	bool			wait;
	bool			is_done;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	hunger_lock;
	t_core			*core;
}					t_philo;

typedef struct s_core
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				eat_limit;
	atomic_int		living_state;
	t_philo			**philos;
	pthread_mutex_t	write_lock;
	atomic_bool		initialized;
	atomic_bool		finished;
}					t_core;

// Custom Functions

int			checker(int ac, char **av);
int			ph_atoi(const char *str);
int			isdigit(int c);
void		*philo_brain(void *in);
long long	get_current_time(void);
int			ph_usleep(long long microseconds);
int			is_even(int in);
int			checkdeath(t_core *core);
int			checkhunger(t_philo *philo, t_core *core);
void		*ph_monitor(void *in);
void		activity_logger(t_philo *philo, char *in);
int			fillcore(t_core *core, char **av);

#endif