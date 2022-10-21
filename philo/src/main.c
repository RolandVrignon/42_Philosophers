/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:09:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/21 14:10:43 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	usage(void)
{
	printf("Args specified are incorrect, you need at least 4 and at most 5\n");
	printf("For example : ./philo 5 2 1 2 9\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_philosophers	*philos;

	if (ac != 5 && ac != 6)
		return (usage());
	if (!check_args(av))
		return (0);
	philos = set_data(ac, av);
	if (!philos)
		return (0);
	if (philos->nb > 1)
		thread_process(philos);
	else
		lonely_process(philos);
	free_philos(philos);
	return (0);
}
