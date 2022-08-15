/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:10:00 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/15 12:56:47 by rvrignon         ###   ########.fr       */
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
	}
	pthread_mutex_unlock(&philo->status_mutex);
	return (return_val);
}

void	set_status(t_philo *philo, t_status status)
{
	if (pthread_mutex_lock(&philo->status_mutex) == 0)
		philo->status = status;
	pthread_mutex_unlock(&philo->status_mutex);
}

int is_finish(t_philosophers *philos)
{
	int value;
	
	if (pthread_mutex_lock(&philos->global_mutex) == 0)
	{
		value = philos->finish;
		pthread_mutex_unlock(&philos->global_mutex);	
	}
	return (value);
}

void set_finish(t_philosophers *philos)
{
	if (pthread_mutex_lock(&philos->global_mutex) == 0)
	{
		philos->finish++;
		pthread_mutex_unlock(&philos->global_mutex);	
	}
}

int	kill_process(int eat, t_philo *philo)
{
	if (someone_died(philo))
		return (1);
	if (eat > 0 && everybody_ate(philo))
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

int	everybody_ate(t_philo *philo)
{
	int	id;

	id = philo->id;
	philo = philo->next;
	while (philo->id != id)
	{
		if (!get_status(philo, done))
			return (0);
		philo = philo->next;
	}
	if (!get_status(philo, done))
		return (0);
	return (1);
}
