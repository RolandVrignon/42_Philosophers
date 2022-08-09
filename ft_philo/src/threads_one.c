/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 12:49:58 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void* routine(void *args)
{
	t_philosophers	*philos;
	t_philo		 	*philo;

	philos = get_struct();
	philo = (t_philo *) args;
	wait_philo(philo, philos);
	usleep(10000);
	if (philos->eatsnb > 0)
		routine_whileeat(philos, philo);
	else
		routine_whiledeath(philos, philo);
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
			printf("%ld %d died\n", get_Timestamp(philos), philo->id);
		else if (has_fork(philos, philo))
		{
			printf("%ld %d has taken a fork\n", get_Timestamp(philos), philo->id);
			printf("%ld %d is eating\n", get_Timestamp(philos), philo->id);
		}
		else if (is_sleeping(philos, philo))
			printf("%ld %d is sleeping\n", get_Timestamp(philos), philo->id);
		else if (is_thinking(philos, philo))
			printf("%ld %d is thinking\n", get_Timestamp(philos), philo->id);
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