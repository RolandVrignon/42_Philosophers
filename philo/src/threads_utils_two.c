/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:03:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/22 01:48:11 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_dead(t_philo *philo)
{
	t_philosophers	*philos;
	int				value;

	philos = get_struct();
	value = 0;
	if (pthread_mutex_lock(&philos->global_mutex) == 0)
	{
		if (get_tmstmp() - philo->gotfork_ms >= philos->time_die_ms)
		{
			philos->finish = 1;
			value = 1;
		}
		pthread_mutex_unlock(&philos->global_mutex);
	}
	return (value);
}

int	can_eat(t_philo *philo)
{
	t_philosophers	*philos;
	unsigned int	gotsleep;

	philos = get_struct();
	gotsleep = philo->gotsleep_ms;
	if (gotsleep == 1 || get_tmstmp() - gotsleep > philos->time_eat_ms)
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

int	someone_died(t_philosophers *philos)
{
	int	value;

	if (pthread_mutex_lock(&philos->global_mutex) == 0)
	{
		value = philos->finish;
		pthread_mutex_unlock(&philos->global_mutex);
	}
	return (value);
}
