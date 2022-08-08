/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:55:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 16:21:31 by rvrignon         ###   ########.fr       */
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