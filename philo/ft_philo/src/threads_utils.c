/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:10:00 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/21 13:51:38 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_status(t_philo *philo, t_status status)
{
	int			return_val;
	t_status	test;

	return_val = 0;
	if (pthread_mutex_lock(&philo->status_mutex) == 0)
	{
		test = philo->status;
		if (test == status)
			return_val = 1;
		pthread_mutex_unlock(&philo->status_mutex);
	}
	return (return_val);
}

void	set_status(t_philo *philo, t_status status)
{
	if (pthread_mutex_lock(&philo->status_mutex) == 0)
		philo->status = status;
	pthread_mutex_unlock(&philo->status_mutex);
}

int	is_finish(t_philosophers *philos)
{
	int	value;

	if (pthread_mutex_lock(&philos->global_mutex) == 0)
	{
		value = philos->finish;
		pthread_mutex_unlock(&philos->global_mutex);
	}
	return (value);
}

void	set_finish(t_philosophers *philos)
{
	if (pthread_mutex_lock(&philos->global_mutex) == 0)
	{
		philos->finish++;
		pthread_mutex_unlock(&philos->global_mutex);
	}
}

int	kill_process(t_philosophers *philos, t_philo *philo)
{
	int	value;
	int	nb;

	value = 0;
	if (someone_died(philos))
		return (1);
	if (pthread_mutex_lock(&philos->global_mutex) == 0)
	{
		nb = philos->nb;
		if (philos->eatsnb > 0 && everybody_ate(philo, nb))
			value = 1;
		pthread_mutex_unlock(&philos->global_mutex);
	}
	return (value);
}
