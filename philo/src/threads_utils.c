/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:10:00 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/21 19:16:12 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_status(t_philo *philo, t_status status)
{
	int			return_val;

	return_val = 0;
	if (pthread_mutex_lock(&philo->status_mutex) == 0)
	{
		if (philo->status == status)
			return_val = 1;
		pthread_mutex_unlock(&philo->status_mutex);
	}
	return (return_val);
}

void	set_finish(t_philosophers *philos)
{
	if (pthread_mutex_lock(&philos->global_mutex) == 0)
	{
		philos->finish++;
		pthread_mutex_unlock(&philos->global_mutex);
	}
}
