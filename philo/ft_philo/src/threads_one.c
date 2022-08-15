/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/15 12:56:16 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_forks(t_philosophers *philos, t_philo *philo)
{
	int id;

	(void)philos;
	id = philo->id;
	philo = philo->next;
	while (philo->id != id)
	{
		if (pthread_mutex_lock(&philo->status_mutex) == 0)
		{
			if (philo->status == eat || philo->status == ready_to_eat)
			{
				pthread_mutex_unlock(&philo->fork_mutex);
				pthread_mutex_unlock(&philo->next->fork_mutex);
			}
		}
		philo = philo->next;
	}
	return ;
}

void	*routine(void *args)
{
	t_philosophers	*philos;
	t_philo			*philo;
	
	philos = get_struct();
	philo = (t_philo *) args;
	if (philo->id % 2 != 0)
		usleep(15000);
	while (1)
	{
		if (is_finish(philos))
			return (NULL);
		else if (get_status(philo, think) || get_status(philo, start))
			set_status(philo, ready_to_fork);
		usleep(10000);
	}
	return (NULL);
}

void	*log_philo(void *args)
{
	t_philosophers	*philos;
	t_philo			*philo;

	philos = (t_philosophers *)args;
	philo = philos->philo;
	while (1)
	{
		if (kill_process(philos->eatsnb, philo))
		{
			set_finish(philos);
			break ;
		}
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
			if (philo->status == ready_to_fork && !get_status(philo->next, eat) && !get_status(philo->prev, eat))
			{
				pthread_mutex_lock(&philo->fork_mutex);
				pthread_mutex_lock(&philo->next->fork_mutex);
				philo->status = ready_to_eat;
				printf("%ld %d has taken a fork\n", get_tmstmp(), philo->id);
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
				philo->status = sleeps;
				philo->eatsnb -= 1;
				philo->gotsleep_ms = get_tmstmp();
				pthread_mutex_unlock(&philo->fork_mutex);
				pthread_mutex_unlock(&philo->next->fork_mutex);
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
	t_philo		*philo;
	pthread_t	logth;
	int			i;

	i = 0;
	philo = philos->philo;
	pthread_mutex_init(&philos->global_mutex, NULL);
	if (pthread_create(&logth, NULL, &log_philo, (void *)philos) != 0)
		perror("Failed to create thread");
	philo_process(philos, philo, i);
	if (pthread_join(logth, NULL) != 0)
		perror("Failed to join thread");
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
