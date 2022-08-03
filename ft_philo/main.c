/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:09:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/03 11:56:48 by rvrignon         ###   ########.fr       */
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

int	check_args(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				ft_printf("One of args is not an int\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

t_philo *philo_lstaddback(t_philo *philo, t_philosophers *philos, int i)
{
	t_philo *tmp;
	t_philo *first;

	first = philo;
	while (philo->next != NULL)
		philo = philo->next;
	tmp = (t_philo *)malloc(sizeof(t_philo));
	if (!tmp)
		return (NULL);
	tmp->id = i + 1;
	tmp->time_die = philos->time_die;
	tmp->time_eat = philos->time_eat;
	tmp->time_sleep = philos->time_sleep;
	tmp->eatsnb = philos->eatsnb;
	philo->next = tmp;
	return (first);
}

t_philo *create_philos(char **av, t_philosophers *philos)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = 1;
	philo->time_die = philos->time_die;
	philo->time_eat = philos->time_eat;
	philo->time_sleep = philos->time_sleep;
	philo->eatsnb = philos->eatsnb;
	philo->next = NULL;
	i = 1;
	while (i < ft_atoi(av[1]))
	{
		philo = philo_lstaddback(philo, philos, i);
		if (!philo)
			return (NULL);
		i++;
	}
	return (philo);
}

t_philosophers *set_data(int ac, char **av)
{
	t_philosophers *philos;

	philos = (t_philosophers *)malloc(sizeof(t_philosophers));
	if (!philos)
		return (NULL);
	philos->time_die = ft_atoi(av[2]);
	philos->time_eat = ft_atoi(av[3]);
	philos->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philos->eatsnb = ft_atoi(av[5]);
	else
		philos->eatsnb = -1;
	philos->philo = create_philos(av, philos);
	if (!philos->philo)
		return (NULL);
	return (philos);
}

void	free_philos(t_philosophers *philos)
{
	t_philo *philo;
	t_philo *tmp;
	
	philo = philos->philo;
	while(philo)
	{
		tmp = philo;
		philo = philo->next;
		free(tmp);
	}
	free(philos);
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