/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 21:55:45 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int check_health(t_philosophers *philos)
{
	if ((now() - philos->today * 1000000) > philos->time_die_s)
		return (0);
	return (1);
}

int someone_died(t_philosophers *philos)
{
	t_philo *philo;
	int		i;

	i = 0;
	philo = philos->philo;
	while (i++ < philos->nb)
	{
		if (philo->is_dead)
			return (1);
		philo = philo->next;
	}
	return (0);
}

int everybody_ate(t_philosophers *philos)
{
	t_philo *philo;
	int		i;

	i = 0;
	philo = philos->philo;
	while (i++ < philos->nb)
	{
		if (philo->eatsnb > 0)
			return (0);
		philo = philo->next;
	}
	return (1);
}

void* routine(void *args)
{
	t_philosophers	*philos;
	t_philo		 	*philo;

	philos = get_struct();
	philo = (t_philo *) args;
	if (philo->id % 2 != 0 && philo->eatsnb == philos->eatsnb)
		usleep(1000);
	while(!someone_died(philos) && philo->eatsnb > 0)
	{
		if (pthread_mutex_lock(&philo->forkMutex) ==  0)
		{
			if (pthread_mutex_lock(&philo->next->forkMutex) == 0)
			{
				philo->gotfork_ms = get_Timestamp(philos);
				usleep(philos->time_eat_s * 1000000);
				pthread_mutex_unlock(&philo->forkMutex);
				pthread_mutex_unlock(&philo->next->forkMutex);
				usleep(philos->time_sleep_s * 1000000);
			}
		}
	}
	return (NULL);
}

void *log_philo(void *args)
{
	t_philosophers	*philos;
	t_philo			*philo;
	
	philos = (t_philosophers *)args;
	philo = philos->philo;
	while(!someone_died(philos) && !everybody_ate(philos))
	{
		if (!philo->is_eating && get_Timestamp(philos) - philo->gotsleep_ms > philos->time_die_s * 1000)
		{
			printf("%d %d died\n", philo->gotsleep_ms + philos->time_die_s * 1000, philo->id);
			philo->is_dead = 1;
		}
		if (philo->gotfork_ms != 0 && !philo->is_eating)
		{
			printf("%d %d has taken a fork\n", philo->gotfork_ms, philo->id);
			philo->is_eating = 1;
			printf("%d %d is eating\n", philo->gotfork_ms, philo->id);
			philo->eatsnb -= 1;
		}
		if (philo->is_eating && get_Timestamp(philos) - philo->gotfork_ms > philos->time_eat_s * 1000)
		{
			philo->gotsleep_ms = philo->gotfork_ms + philos->time_eat_s * 1000;
			philo->gotfork_ms = 0;
			philo->is_eating = 0;
			printf("%ld %d is sleeping\n", get_Timestamp(philos), philo->id);
		}
		philo = philo->next;
	}
	return (NULL);
}

void thread_process(t_philosophers *philos)
{	
	pthread_t logth;

	if (pthread_create(&logth, NULL, &log_philo, (void *)philos) != 0)
		perror("Failed to create thread");
	pthread_mutex_init(&philos->printfMutex, NULL);
	philo_process(philos);
	if (pthread_join(logth, NULL) != 0)
		perror("Failed to join thread");
	pthread_mutex_destroy(&philos->printfMutex);
}