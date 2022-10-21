/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/21 14:11:50 by rvrignon         ###   ########.fr       */
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
		usleep(1000);
	while (1)
	{
		if (is_finish(philos))
			return (NULL);
		else if (get_status(philo, think) || get_status(philo, start))
			set_status(philo, ready_to_fork);
		usleep(1000);
	}
	return (NULL);
}

void	*log_philo(void *args)
{
	t_philosophers	*philos;
	t_philo			*philo;

	philos = (t_philosophers *)args;
	philo = philos->philo;
	usleep(2000);
	while (1)
	{
		if (kill_process(philos, philo))
		{
			set_finish(philos);
			break ;
		}
		else if (pthread_mutex_lock(&philo->status_mutex) == 0)
		{
			one(philo);
			two(philo);
			pthread_mutex_unlock(&philo->status_mutex);
		}
		philo = philo->next;
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
	pthread_t	logth;
	int			i;

	i = 0;
	philo = philos->philo;
	pthread_mutex_init(&philos->global_mutex, NULL);
	if (pthread_create(&logth, NULL, &log_philo, (void *)philos) != 0)
		return ;
	philo_process(philos, philo, i);
	if (pthread_join(logth, NULL) != 0)
		return ;
	pthread_mutex_destroy(&philos->global_mutex);
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
	while (i-- > 1)
	{
		pthread_mutex_destroy(&philo->fork_mutex);
		pthread_mutex_destroy(&philo->status_mutex);
		philo = philo->next;
	}
}
