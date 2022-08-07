/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/07 19:03:19 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static char get_Timestamp()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    printf("%ld.%ld ", current_time.tv_sec, current_time.tv_usec);
    return ('-'); 
}

void* routine(void* args)
{
	t_philo *philo;

	philo = (t_philo *) args;
	while (philo->eatsnb != 0)
	{
		if (pthread_mutex_trylock(&philo->next->forkMutex) == 0 &&
			pthread_mutex_trylock(&philo->forkMutex) == 0)
		{
			printf("%c Philo %d has taken a fork\n", get_Timestamp(), philo->id);
			printf("%c Philo %d is eating\n",get_Timestamp(), philo->id);
			sleep(philo->time_eat);
			pthread_mutex_unlock(&philo->next->forkMutex);
			pthread_mutex_unlock(&philo->forkMutex);
			philo->eatsnb -= 1;
            printf("%c Philo %d is sleeping\n",get_Timestamp(), philo->id);
            sleep(philo->time_sleep);
		}
		else
		{
            
		}
	}
	return (NULL);
}

void thread_process(t_philosophers *philos)
{
	t_philo *philo;
	int		i;

	philo = philos->philo;
	i = 0;
	while (i++ < philos->nb)
	{
        pthread_mutex_init(&philo->forkMutex, NULL);
		philo = philo->next;
	}
	i = 0;
	while (i++ < philos->nb)
	{
		if (pthread_create(&philo->th, NULL, &routine, (void *) philo) != 0)
			perror("Failed to create mutex");
		philo = philo->next;
	}
	i = 0;
	while (i++ < philos->nb)
	{
		if (pthread_join(philo->th, NULL) != 0)
			perror("Failed to create mutex");
		philo = philo->next;
	}
	i = 0;
	while (i++ < philos->nb)
	{
		pthread_mutex_destroy(&philo->forkMutex);
		philo = philo->next;
	}
}