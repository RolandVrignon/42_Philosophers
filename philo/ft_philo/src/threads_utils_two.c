/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:03:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/15 13:12:48 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_dead(t_philo *philo)
{
	t_philosophers	*philos;

	philos = get_struct();
	if (get_tmstmp() - philo->gotfork_ms >= philos->time_die_ms)
		return (1);
	return (0);
}

int	can_eat(t_philo *philo)
{
	if (!get_status(philo->next, eat) && !get_status(philo->prev, eat))
		return (1);
	return (0);
}

int	finish_eating(t_philo *philo)
{
	t_philosophers	*philos;

	philos = get_struct();
	if (get_tmstmp() - philo->gotfork_ms >= philos->time_eat_ms)
		return (1);
	return (0);
}

int	finish_sleeping(t_philo *philo)
{
	t_philosophers	*philos;

	philos = get_struct();
	if (get_tmstmp() - philo->gotsleep_ms >= philos->time_sleep_ms)
		return (1);
	return (0);
}

int	someone_died(t_philo *philo)
{
	int	id;

	id = philo->id;
	philo = philo->next;
	if (get_status(philo, died))
		return (1);
	while (philo->id != id)
	{
		if (get_status(philo, died))
			return (1);
		philo = philo->next;
	}
	return (0);
}
