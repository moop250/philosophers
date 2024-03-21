/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:29 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/21 17:35:18 by hlibine          ###   ########.fr       */
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
	pthtread_t	thread;
	int			id;
	int			living_state;
	size_t		last_meal;
}				t_philo;

typedef struct s_philoll
{
	t_philo				content;
	struct s_threads	*next;
}						t_philoll;

// Custom Functions

int		checker(int ac, char **av);
int		atoi(const char *str);
int		isdigit(int c);

#endif