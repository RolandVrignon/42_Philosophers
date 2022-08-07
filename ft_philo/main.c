/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:09:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/07 18:10:46 by rvrignon         ###   ########.fr       */
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

static void	print_data(t_philosophers *philos)
{
	t_philo			*philo;
	int				i;

	printf("\n-----------------------------------------------------\n\n");
	printf("Philos are setted up\n");
	printf("We have \t\t\t: %d philosophers\nThey die after\t\t\t: %d sec\nThey eat while\t\t\t: %d sec\nThey sleep while\t\t: %d sec\nthey have to eat\t\t: %d times\n", philos->nb, philos->time_die, philos->time_eat, philos->time_sleep, philos->eatsnb);
	philo = philos->philo;
	i = 0;
	while (i < philos->nb)
	{
		printf("Philosopher %d is set up and dies in %d seconds and should eat %d times\n",philo->id, philo->time_die, philo->eatsnb);
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
	thread_process(philos);
	print_data(philos);
	free_philos(philos);
	return (0);
}
