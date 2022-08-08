/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 16:43:28 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void* routine(void *args)
{
	t_philosophers	*philos;
	t_philo		 	*philo;

	philos = get_struct();
	philo = (t_philo *) args;
	if (pthread_mutex_lock(&philos->printfMutex) ==  0)
	{
		printf("Hello from philo : %d\n", philo->id);
		pthread_mutex_unlock(&philos->printfMutex);
	}
	return (NULL);
}

void thread_process(t_philosophers *philos)
{	
	pthread_mutex_init(&philos->printfMutex, NULL);
	philo_process(philos);
	pthread_mutex_destroy(&philos->printfMutex);
}