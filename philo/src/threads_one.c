/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/11/07 17:06:57 by rvrignon         ###   ########.fr       */
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

	philo = philos->philo;
	pthread_mutex_init(&philos->global_mutex, NULL);
	pthread_mutex_init(&philos->printf_mutex, NULL);
	if (!philo_process(philos, philo))
	{
		destroy_all_philos_mutex(philos, philo);
		detach_all_philos(philos, philo);
	}
}

int		philo_thread_create(t_philosophers *philos, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philos->nb)
	{
		if (pthread_create(&philo->th, NULL, &routine, (void *) philo) != 0)
			return (0);
		philo = philo->next;
	i++;
	}
	return (1);
}

int		philo_thread_join(t_philosophers *philos, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philos->nb)
	{
		if (pthread_join(philo->th, NULL) != 0)
			return (0);
		philo = philo->next;
	i++;
	}
	return (1);
}

void	destroy_all_philos_mutex(t_philosophers *philos, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philos->nb)
	{
		pthread_mutex_destroy(&philo->fork_mutex);
		pthread_mutex_destroy(&philo->status_mutex);
		philo = philo->next;
	i++;
	}
}

void	detach_all_philos(t_philosophers *philos, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philos->nb)
	{
		pthread_detach(philo->th);
		philo = philo->next;
	i++;
	}
}

int	philo_process(t_philosophers *philos, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philos->nb)
	{
		pthread_mutex_init(&philo->fork_mutex, NULL);
		pthread_mutex_init(&philo->status_mutex, NULL);
		philo = philo->next;
		i++;
	}
	if (!philo_thread_create(philos, philo))
		return (0);
	if (!philo_thread_join(philos, philo))
		return (0);
	return (1);
}
