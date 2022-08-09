/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:55:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 15:52:46 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_process(t_philosophers *philos, int i)
{
	t_philo		*philo;

	philo = philos->philo;
	while (i++ < philos->nb)
	{
		pthread_mutex_init(&philo->fork_mutex, NULL);
		philo = philo->next;
	}
	while (i-- > 1)
	{
		if (pthread_create(&philo->th, NULL, &routine, (void *) philo) != 0)
			perror("Failed to create mutex");
		philo = philo->next;
	}
	while (i++ < philos->nb)
	{
		if (pthread_join(philo->th, NULL) != 0)
			perror("Failed to create mutex");
		philo = philo->next;
	}
	while (i-- > 1)
	{
		pthread_mutex_destroy(&philo->fork_mutex);
		philo = philo->next;
	}
}

time_t	get_tmstmp(t_philosophers *philos)
{
	time_t			mili;

	mili = now() - philos->today;
	return (mili);
}

time_t	now(void)
{
	struct timeval	current_time;
	time_t			mili;

	gettimeofday(&current_time, NULL);
	mili = current_time.tv_sec
		* (time_t)1000 + current_time.tv_usec / (time_t)1000;
	return (mili);
}

void	routine_whiledeath(t_philosophers *philos, t_philo *philo)
{
	while (!someone_died(philos))
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
