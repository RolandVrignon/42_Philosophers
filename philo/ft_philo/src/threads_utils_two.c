/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:03:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 15:51:46 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_sleeping(t_philosophers *philos, t_philo *philo)
{
	if (!philo->is_dead && philo->is_eating
		&& he_finished_eating(philos, philo))
	{
		philo->gotsleep_ms = get_tmstmp(philos);
		philo->is_sleeping = 1;
		return (1);
	}
	return (0);
}

// Finish sleeping -- start thinking

int	he_finished_sleeping(t_philosophers *philos, t_philo *philo)
{
	if (get_tmstmp(philos) - philo->gotsleep_ms > philos->time_sleep_ms)
	{
		philo->is_sleeping = 0;
		return (1);
	}
	return (0);
}

int	is_thinking(t_philosophers *philos, t_philo *philo)
{
	if (!philo->is_dead && philo->is_sleeping
		&& he_finished_sleeping(philos, philo))
	{
		philo->start_thinking_ms = get_tmstmp(philos);
		philo->is_thinking = 1;
		return (1);
	}
	return (0);
}

void	wait_philo(t_philo *philo, t_philosophers *philos)
{
	if (philo->id % 2 != 0 && philo->eatsnb == philos->eatsnb)
	{
		if (pthread_mutex_lock(&philos->printf_mutex) == 0)
			printf("%ld %d is thinking\n", get_tmstmp(philos), philo->id);
		pthread_mutex_unlock(&philos->printf_mutex);
		usleep(10000);
	}
}

void	routine_whileeat(t_philosophers *philos, t_philo *philo)
{
	while (!someone_died(philos) && philo->eatsnb > 0)
	{
		if (philo->is_thinking)
		{
			if (pthread_mutex_lock(&philo->fork_mutex) == 0)
			{
				if (pthread_mutex_lock(&philo->next->fork_mutex) == 0)
				{
					philo->gotfork_ms = get_tmstmp(philos);
					usleep(philos->time_eat_ms * 1000);
					pthread_mutex_unlock(&philo->fork_mutex);
					pthread_mutex_unlock(&philo->next->fork_mutex);
					usleep(1000);
				}
			}
		}
	}
	return ;
}
