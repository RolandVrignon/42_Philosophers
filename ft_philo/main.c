/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:09:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/03 11:59:23 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ac = 1 => number_of_philosophers
// ac = 2 => time_to_die
// ac = 3 => time_to_eat
// ac = 4 => time_to_sleep
// ac = 5 => number_of_times_each_philosopher_must_eat

int	usage(void)
{
	ft_printf("Args specified are incorrect, you need at least 4 and at most 5\n");
	ft_printf("For example : ./philo 5 2 1 2 9\n");
	return (0);
}


int	main(int ac, char **av)
{
	t_philosophers *philos;
	t_philo *philo;
	
	if (ac != 5 && ac != 6)
		return (usage());
	if (!check_args(av))
		return (0);
	philos = set_data(ac, av);
	if (!philos)
		return (0);
	ft_printf("Philos are setted up\n");
	ft_printf("Philosophers dead time is\t: %d sec\nPhilosophers eat time is\t: %d sec\nPhilosophers sleep time \t: %d sec\nPhilosophers eat numbers is\t: %d sec\n", philos->time_die, philos->time_eat, philos->time_sleep, philos->eatsnb);
	philo = philos->philo;
	while (philo)
	{
		ft_printf("Philosopher %d is set up and dies in %d seconds and should eat %d times\n", philo->id, philo->time_die, philo->eatsnb);
		philo = philo->next;
	}
	free_philos(philos);
	return (0);
}