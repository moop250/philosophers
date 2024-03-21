/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:29 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/21 16:52:14 by hlibine          ###   ########.fr       */
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

typedef struct s_threads
{
	pthread_t			thread;
	struct s_threads	*next;
}						t_threads;

// Custom Functions

int		checker(int ac, char **av);
int		atoi(const char *str);
int		isdigit(int c);

#endif