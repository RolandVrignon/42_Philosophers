/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/22 00:41:02 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *args)
{
	t_philosophers	*philos;
	t_philo			*philo;

	philos = get_struct();
	philo = (t_philo *) args;
	if (philo->id % 2 != 0)
		usleep((philos->time_eat_ms - 1) * 1000);
	while (!someone_died(philos))
	{	
		if (pthread_mutex_lock(&philo->status_mutex) == 0)
		{
			if (philo->status == done)
			{
				pthread_mutex_unlock(&philo->status_mutex);
				pthread_mutex_destroy(&philo->status_mutex);
				return (NULL);
			}
			define_status(philo);
			pthread_mutex_unlock(&philo->status_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}

void	lonely_process(t_philosophers *philos)
{	
	printf("%ld 1 has taken a fork\n", get_tmstmp());
	usleep(philos->time_die_ms * 1000);
	printf("%ld 1 died\n", get_tmstmp());
}

void	thread_process(t_philosophers *philos)
{	
	t_philo		*philo;
	int			i;

	i = 0;
	philo = philos->philo;
	pthread_mutex_init(&philos->global_mutex, NULL);
	pthread_mutex_init(&philos->printf_mutex, NULL);
	philo_process(philos, philo, i);
}

void	philo_process(t_philosophers *philos, t_philo *philo, int i)
{
	while (i++ < philos->nb)
	{
		pthread_mutex_init(&philo->fork_mutex, NULL);
		pthread_mutex_init(&philo->status_mutex, NULL);
		philo = philo->next;
	}
	while (i-- > 1)
	{
		if (pthread_create(&philo->th, NULL, &routine, (void *) philo) != 0)
			return ;
		philo = philo->next;
	}
	while (i++ < philos->nb)
	{
		if (pthread_join(philo->th, NULL) != 0)
			return ;
		philo = philo->next;
	}
}
