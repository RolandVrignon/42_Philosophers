/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/14 16:19:11 by rvrignon         ###   ########.fr       */
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
		usleep (15000);
	while (1)
	{
		if (kill_proces(philos, philo))
			return (NULL);
		else if (get_status(philo, think) || get_status(philo, start))
		{
			if (pthread_mutex_lock(&philo->fork_mutex) == 0)
				set_status(philo, fork_one);
		}
		else if (get_status(philo, wait_one))
		{
			if (pthread_mutex_lock(&philo->next->fork_mutex) == 0)
				set_status(philo, fork_two);
		}
	}
	return (NULL);
}

void	*log_philo(void *args)
{
	t_philosophers	*philos;
	t_philo			*philo;

	philos = (t_philosophers *)args;
	philo = philos->philo;
	usleep(1000);
	while (1)
	{
			if (kill_proces(philos, philo))
				return (NULL);
			else if (pthread_mutex_lock(&philo->status_mutex) == 0)
			{
				if (philo->eatsnb == 0)
					philo->status = done;
				if (philo->status != done && get_tmstmp() - philo->gotfork_ms >= philos->time_die_ms)
				{
					philo->status = died;
					printf("%ld %d died\n", get_tmstmp(), philo->id);
				}
				if (philo->status == think && philo->start_thinking_ms != 0)
				{
					philo->start_thinking_ms = 0;
					printf("%ld %d is thinking\n", get_tmstmp(), philo->id);
				}
				if (philo->status == fork_one)
				{
					philo->status = wait_one;
					printf("%ld %d has taken a fork\n", get_tmstmp(), philo->id);
				}
				if (philo->status == fork_two)
				{
					philo->status = ready_to_eat;
					printf("%ld %d has taken a fork\n", get_tmstmp(), philo->id);
				}
				if (philo->status == ready_to_eat)
				{
					philo->status = eat;
					philo->start_thinking_ms = 0;
					philo->gotfork_ms = get_tmstmp();
					printf("%ld %d is eating\n", get_tmstmp(), philo->id);
				}
				if (philo->status == eat && get_tmstmp() - philo->gotfork_ms >= philos->time_eat_ms)
				{
					pthread_mutex_unlock(&philo->fork_mutex);
					pthread_mutex_unlock(&philo->next->fork_mutex);
					philo->status = sleeps;
					philo->eatsnb -= 1;
					philo->gotsleep_ms = get_tmstmp();
					printf("%ld %d is sleeping\n", get_tmstmp(), philo->id);
				}
				if (philo->status == sleeps && get_tmstmp() - philo->gotsleep_ms >= philos->time_sleep_ms)
				{
					philo->gotsleep_ms = 0;
					philo->start_thinking_ms = get_tmstmp();
					philo->status = think;
				}
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
	pthread_t	logth;
	int			i;

	i = 0;
	if (pthread_create(&logth, NULL, &log_philo, (void *)philos) != 0)
		perror("Failed to create thread");
	philo_process(philos, i);
	if (pthread_join(logth, NULL) != 0)
		perror("Failed to join thread");
}

void	philo_process(t_philosophers *philos, int i)
{
	t_philo		*philo;

	philo = philos->philo;
	while (i++ < philos->nb)
	{
		philo->status = start;
		pthread_mutex_init(&philo->fork_mutex, NULL);
		pthread_mutex_init(&philo->status_mutex, NULL);
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
		pthread_mutex_destroy(&philo->status_mutex);
		philo = philo->next;
	}
}
