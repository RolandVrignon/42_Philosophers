/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:17:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 15:54:18 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *args)
{
	t_philosophers	*philos;
	t_philo			*philo;

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

void	*log_philo(void *args)
{
	t_philosophers	*philos;
	t_philo			*ph;

	philos = (t_philosophers *)args;
	ph = philos->philo;
	while (!someone_died(philos) && !everybody_ate(philos))
	{
		if (pthread_mutex_lock(&philos->printf_mutex) == 0)
		{
			if (he_died(philos, ph))
				printf("%ld %d died\n", get_tmstmp(philos), ph->id);
			else if (has_fork(philos, ph))
			{
				printf("%ld %d has taken a fork\n", get_tmstmp(philos), ph->id);
				printf("%ld %d is eating\n", get_tmstmp(philos), ph->id);
			}
			else if (is_sleeping(philos, ph))
				printf("%ld %d is sleeping\n", get_tmstmp(philos), ph->id);
			else if (is_thinking(philos, ph))
				printf("%ld %d is thinking\n", get_tmstmp(philos), ph->id);
			pthread_mutex_unlock(&philos->printf_mutex);
		}
		ph = ph->next;
	}
	return (NULL);
}

void	thread_process(t_philosophers *philos)
{	
	pthread_t	logth;
	int			i;

	i = 0;
	if (pthread_create(&logth, NULL, &log_philo, (void *)philos) != 0)
		perror("Failed to create thread");
	pthread_mutex_init(&philos->printf_mutex, NULL);
	philo_process(philos, i);
	if (pthread_join(logth, NULL) != 0)
		perror("Failed to join thread");
	pthread_mutex_destroy(&philos->printf_mutex);
}
