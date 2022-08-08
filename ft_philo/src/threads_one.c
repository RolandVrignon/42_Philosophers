/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 18:46:22 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void* routine(void *args)
{
	t_philosophers	*philos;
	t_philo		 	*philo;

	philos = get_struct();
	philo = (t_philo *) args;
	
	while(philo->eatsnb > 0)
	{
		if (pthread_mutex_lock(&philo->forkMutex) ==  0)
		{
			if (pthread_mutex_lock(&philo->next->forkMutex) == 0)
			{
				philo->time_sleep = philos->time_sleep;
				if (pthread_mutex_lock(&philos->printfMutex) == 0)
				{
					printf("%ld %d has taken a fork\n",get_Timestamp(philos), philo->id);
					pthread_mutex_unlock(&philos->printfMutex);
				}
				if (pthread_mutex_lock(&philos->printfMutex) == 0)
				{
					printf("%ld %d is eating\n",get_Timestamp(philos), philo->id);
					pthread_mutex_unlock(&philos->printfMutex);
				}
				usleep(philo->time_eat);
				pthread_mutex_unlock(&philo->forkMutex);
				pthread_mutex_unlock(&philo->next->forkMutex);
				philo->eatsnb -= 1;
				if (pthread_mutex_lock(&philos->printfMutex) == 0)
				{
					printf("%ld %d is sleeping\n",get_Timestamp(philos), philo->id);
					pthread_mutex_unlock(&philos->printfMutex);
				}
				usleep(philo->time_sleep);
			}
		}
	}
	return (NULL);
}

void thread_process(t_philosophers *philos)
{	
	pthread_mutex_init(&philos->printfMutex, NULL);
	philo_process(philos);
	pthread_mutex_destroy(&philos->printfMutex);
}