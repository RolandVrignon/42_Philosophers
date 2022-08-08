/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 23:24:00 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void* routine(void *args)
{
	t_philosophers	*philos;
	t_philo		 	*philo;

	philos = get_struct();
	philo = (t_philo *) args;
	if (philo->id % 2 != 0 && philo->eatsnb == philos->eatsnb)
		usleep(10000);	
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
		if (he_died(philos, philo))
		{
			printf("%ld %d died\n", get_Timestamp(philos), philo->id);
			philo->is_dead = 1;
		}
		else if (has_fork(philos, philo))
		{
			philo->is_thinking = 0;
			printf("%ld %d has taken a fork\n", get_Timestamp(philos), philo->id);
			philo->is_eating = 1;
			printf("%ld %d is eating\n", get_Timestamp(philos), philo->id);
		}
		else if (is_sleeping(philos, philo))
		{
			printf("%ld %d is sleeping\n", get_Timestamp(philos), philo->id);
			philo->eatsnb -= 1;
			philo->gotsleep_ms = philo->gotfork_ms + philos->time_eat_s * 1000;
			philo->gotfork_ms = 0;
			philo->is_eating = 0;
			philo->is_sleeping = 1;
		}
		else if (is_thinking(philos, philo))
		{
			printf("%ld %d is thinking\n", get_Timestamp(philos), philo->id);
			philo->start_thinking_ms = get_Timestamp(philos);
			philo->is_thinking = 1;
			philo->is_sleeping = 0;
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