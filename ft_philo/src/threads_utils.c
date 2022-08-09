/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:10:00 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 13:08:23 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	someone_died(t_philosophers *philos)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = philos->philo;
	while (i++ < philos->nb)
	{
		if (philo->is_dead)
			return (1);
		philo = philo->next;
	}
	return (0);
}

int	everybody_ate(t_philosophers *philos)
{
	t_philo	*philo;
	int		i;

	if (philos->eatsnb == -1)
		return (0);
	i = 0;
	philo = philos->philo;
	while (i++ < philos->nb)
	{
		if (philo->eatsnb > 0)
			return (0);
		philo = philo->next;
	}
	return (1);
}

int	he_died(t_philosophers *philos, t_philo *philo)
{
	if (!philo->start_thinking_ms)
	{
		if (!philo->is_eating && !philo->is_sleeping
			&& get_tmstmp(philos) > philos->time_die_ms)
		{
			philo->is_dead = 1;
			return (1);
		}
	}
	else
	{
		if (!philo->is_eating && !philo->is_sleeping
			&& get_tmstmp(philos) - philo->start_thinking_ms
			> philos->time_die_ms)
		{
			philo->is_dead = 1;
			return (1);
		}
	}
	return (0);
}

int	has_fork(t_philosophers *philos, t_philo *philo)
{
	(void)philos;
	if (!philo->is_dead && !philo->is_sleeping
		&& philo->gotfork_ms && !philo->is_eating)
	{
		philo->is_thinking = 0;
		philo->is_eating = 1;
		return (1);
	}
	return (0);
}

// Finish eating -- start sleeping

int	he_finished_eating(t_philosophers *philos, t_philo *philo)
{
	if (get_tmstmp(philos) - philo->gotfork_ms > philos->time_eat_ms)
	{
		philo->eatsnb -= 1;
		philo->gotfork_ms = 0;
		philo->is_eating = 0;
		return (1);
	}
	return (0);
}
