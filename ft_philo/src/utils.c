/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:58:29 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/03 13:46:57 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	tmp->prev = philo;
	tmp->next = NULL;
	philo->next = tmp;
	return (first);
}

t_philo *philo_addlast(t_philo *philo, t_philosophers *philos, int i)
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
	tmp->prev = philo;
	tmp->next = first;
	philo->next = tmp;
	first->prev = tmp;
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
	philo->prev = NULL;
	i = 1;
	while (i < ft_atoi(av[1]) - 1)
	{
		philo = philo_lstaddback(philo, philos, i);
		if (!philo)
			return (NULL);
		i++;
	}
	philo = philo_addlast(philo, philos, i);
	return (philo);
}

t_philosophers *set_data(int ac, char **av)
{
	t_philosophers *philos;

	philos = (t_philosophers *)malloc(sizeof(t_philosophers));
	if (!philos)
		return (NULL);
	philos->nb = ft_atoi(av[1]);
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
	int		i;
	
	philo = philos->philo;
	i = 0;
	while(i < philos->nb)
	{
		tmp = philo;
		philo = philo->next;
		free(tmp);
		i++;
	}
	free(philos);
}