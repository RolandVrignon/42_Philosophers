/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:10:00 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/14 15:17:59 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int get_status(t_philo *philo, t_status status)
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

void set_status(t_philo *philo, t_status status)
{
	if (pthread_mutex_lock(&philo->status_mutex) == 0)
		philo->status = status;
	pthread_mutex_unlock(&philo->status_mutex);
}

int kill_proces(t_philosophers *philos, t_philo *philo)
{
	if (philos->eatsnb > 0)
	{
		if (someone_died(philos, philo) || everybody_ate(philos, philo))
			return (1);
	}
	else
	{
		if (someone_died(philos, philo))
			return (1);
	}
	return (0);
}

int someone_died(t_philosophers *philos, t_philo *philo)
{
	int i;

	i = 0;
	while (i <= philos->nb)
	{
		if (get_status(philo, died))
			return (1);
		philo = philo->next;
		i++;
	}
	return (0);
}

int everybody_ate(t_philosophers *philos, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philos->nb)
	{
		if (!get_status(philo, done))
			return (0);
		philo = philo->next;
		i++;
	}
	return (1);
}