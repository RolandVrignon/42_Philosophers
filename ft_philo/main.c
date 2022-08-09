/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:09:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 13:11:17 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

// ac = 1 => number_of_philosophers
// ac = 2 => time_to_die
// ac = 3 => time_to_eat
// ac = 4 => time_to_sleep
// ac = 5 => number_of_times_each_philosopher_must_eat

int	usage(void)
{
	printf("Args specified are incorrect, you need at least 4 and at most 5\n");
	printf("For example : ./philo 5 2 1 2 9\n");
	return (0);
}

void	print_data(t_philosophers *philos)
{
	t_philo			*philo;
	int				i;

	printf("\n-----------------------------------------------------\n\n");
	printf("Philos are setted up\n");
	printf("We have \t\t\t: %d philosophers\nThey die after\t\t\t: %d ms\nThey eat while\t\t\t: %d ms\nThey sleep while\t\t: %d ms\nthey have to eat\t\t: %d times\n", philos->nb, philos->time_die_ms, philos->time_eat_ms, philos->time_sleep_ms, philos->eatsnb);
	philo = philos->philo;
	i = 0;
	while (i < philos->nb)
	{
		printf("Philosopher %d is set up, they should eat %d times\n", philo->id, philo->eatsnb);
		philo = philo->next;
		i++;
	}
	printf("\n-----------------------------------------------------\n\n");
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
	print_data(philos);
	if (philos->nb != 0 && philos->eatsnb != 0)
		thread_process(philos);
	printf("%ld Finish execution\n", get_tmstmp(philos));
	print_data(philos);
	free_philos(philos);
	return (0);
}
