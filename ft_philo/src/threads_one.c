/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/07 21:00:36 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char get_Timestamp()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    printf("%ld.%ld ", current_time.tv_sec, current_time.tv_usec);
    return ('-'); 
}

int try_fork_locker(t_philo *philo)
{
    if (pthread_mutex_trylock(&philo->next->forkMutex) == 0)
    {
        if (pthread_mutex_trylock(&philo->forkMutex) == 0)
            return 1;
        else
            pthread_mutex_unlock(&philo->next->forkMutex);
    }
    return 0;
}

void fork_unlocker(t_philo *philo)
{
    pthread_mutex_unlock(&philo->next->forkMutex);
	pthread_mutex_unlock(&philo->forkMutex);
}

int no_death(t_philo *philo)
{
    int id;

    id = philo->id;
    if (philo->time_die <= 0)
        return (0);
    philo = philo->next;
    while(philo->id != id)
    {
        if (philo->time_die <= 0)
            return (0);
        philo = philo->next;
    }
    return (1);
}

void* routine(void* args)
{
	t_philo *philo;

	philo = (t_philo *) args;
	while (philo->eatsnb != 0 && no_death(philo))
	{
		if (try_fork_locker(philo))
		{
			printf("%c Philo %d\thas taken a fork\n", get_Timestamp(), philo->id);
			printf("%c Philo %d\tis eating\n",get_Timestamp(), philo->id);
			usleep(philo->time_eat);
			fork_unlocker(philo);
			philo->eatsnb -= 1;
            if (no_death(philo))
                printf("%c Philo %d\tis sleeping\n",get_Timestamp(), philo->id);
            usleep(philo->time_sleep);
		}
		else
		{
            philo->time_die -= 1;
            usleep(1);
            if (philo->time_die <= 0)
                printf("%c Philo %d\tdied\n",get_Timestamp(), philo->id);
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