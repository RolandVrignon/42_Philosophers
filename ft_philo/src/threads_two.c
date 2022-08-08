/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:55:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 19:09:23 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void philo_process(t_philosophers *philos)
{
	int 	i;
    t_philo *philo;
    
    philo = philos->philo;
	i = 0;
	while (i++ < philos->nb)
	{
        pthread_mutex_init(&philo->forkMutex, NULL);
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
		pthread_mutex_destroy(&philo->forkMutex);
		philo = philo->next;
	}
}

t_philosophers *get_struct(void)
{
    static t_philosophers philos;

    return (&philos);
}

time_t get_Timestamp(t_philosophers *philos)
{
	time_t			mili;
	
    mili = now() - philos->today;
    return (mili); 
}

time_t now(void)
{
	struct timeval	current_time;
	time_t			mili;

	gettimeofday(&current_time, NULL);
	mili = current_time.tv_sec * (time_t)1000 + current_time.tv_usec / (time_t)1000;
	return (mili);
}