/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:18 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/21 17:14:05 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	int	*args;

	if (checker(ac, av) == 1)
		return (1);
	args = malloc(5 * sizeof(int));
	if (!args)
		return (2);
	free(args);
	printf("sucess\n");
	return (0);
}