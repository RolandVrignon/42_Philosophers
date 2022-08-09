/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:10:00 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 12:31:21 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int check_health(t_philosophers *philos)
{
	if ((now() - philos->today * 1000) > philos->time_die_ms)
		return (0);
	return (1);
}

int someone_died(t_philosophers *philos)
{
	t_philo *philo;
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

int everybody_ate(t_philosophers *philos)
{
	t_philo *philo;
	int		i;

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

int he_died(t_philosophers *philos, t_philo *philo)
{
	if (!philo->start_thinking_ms)
	{
		if (!philo->is_eating && !philo->is_sleeping && get_Timestamp(philos) > philos->time_die_ms)
		{
			philo->is_dead = 1;
			return (1);
		}
	}
	else
	{
		if (!philo->is_eating && !philo->is_sleeping && get_Timestamp(philos) - philo->start_thinking_ms > philos->time_die_ms)
		{
			philo->is_dead = 1;
			return (1);
		}
	}
	return (0);
}

int has_fork(t_philosophers *philos, t_philo *philo)
{
	(void)philos;
	if (!philo->is_dead && !philo->is_sleeping && philo->gotfork_ms && !philo->is_eating)
	{
		philo->is_thinking = 0;
		philo->is_eating = 1;
		return (1);
	}
	return (0);
}

// Finish eating -- start sleeping

int he_finished_eating(t_philosophers *philos, t_philo *philo)
{
	if (get_Timestamp(philos) - philo->gotfork_ms > philos->time_eat_ms)
	{
		philo->eatsnb -= 1;
		philo->gotfork_ms = 0;
		philo->is_eating = 0;
		return (1);
	}
	return (0);
}

int is_sleeping(t_philosophers *philos, t_philo *philo)
{
	if (!philo->is_dead && philo->is_eating && he_finished_eating(philos, philo))
	{
		philo->gotsleep_ms = get_Timestamp(philos);
		philo->is_sleeping = 1;
		return (1);
	}
	return (0);
}

// Finish sleeping -- start thinking

int he_finished_sleeping(t_philosophers *philos, t_philo *philo)
{
	if (get_Timestamp(philos) - philo->gotsleep_ms > philos->time_sleep_ms)
	{
		philo->is_sleeping = 0;
		return (1);
	}
	return (0);
}

int is_thinking(t_philosophers *philos, t_philo *philo)
{
	if (!philo->is_dead && philo->is_sleeping && he_finished_sleeping(philos, philo))
	{
		philo->start_thinking_ms = get_Timestamp(philos);
		philo->is_thinking = 1;
		return (1);
	}
	return (0);
}