/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:55:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/22 01:48:56 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	printphilo(t_philo *philo)
{
	t_philosophers	*philos;

	philos = get_struct();
	if (pthread_mutex_lock(&philos->printf_mutex) == 0)
	{
		if (philo->status == died)
			printf("%ld %d died\n", get_tmstmp(), philo->id);
		if (!someone_died(philos))
		{
			if (philo->status == think)
				printf("%ld %d is thinking\n", get_tmstmp(), philo->id);
			else if (philo->status == ready_to_eat)
			{
				printf("%ld %d has taken a fork\n", get_tmstmp(), philo->id);
				printf("%ld %d has taken a fork\n", get_tmstmp(), philo->id);
			}
			else if (philo->status == eat)
				printf("%ld %d is eating\n", get_tmstmp(), philo->id);
			else if (philo->status == sleeps)
				printf("%ld %d is sleeping\n", get_tmstmp(), philo->id);
		}
		pthread_mutex_unlock(&philos->printf_mutex);
	}
}

void	define_status(t_philo *philo)
{
	if (philo->eatsnb == 0)
		philo->status = done;
	if (philo->status != done && is_dead(philo))
	{
		philo->status = died;
		printphilo(philo);
		return ;
	}
	if (philo->status == think && philo->start_thinking_ms != 0)
	{
		philo->start_thinking_ms = 0;
		printphilo(philo);
		philo->status = ready_to_fork;
	}
	if (philo->status == sleeps && finish_sleeping(philo))
	{
		philo->start_thinking_ms = get_tmstmp();
		philo->status = think;
		philo->gotsleep_ms = 0;
	}
	define_status_two(philo);
}

void	define_status_two(t_philo *philo)
{
	if (philo->status == ready_to_fork && can_eat(philo))
	{
		philo->gotfork_ms = get_tmstmp();
		pthread_mutex_lock(&philo->fork_mutex);
		pthread_mutex_lock(&philo->next->fork_mutex);
		philo->gotsleep_ms = 0;
		philo->status = ready_to_eat;
		printphilo(philo);
		philo->start_thinking_ms = 0;
		philo->status = eat;
		printphilo(philo);
		usleep(get_struct()->time_eat_ms * 1000);
		philo->status = sleeps;
		philo->eatsnb -= 1;
		philo->gotsleep_ms = get_tmstmp();
		pthread_mutex_unlock(&philo->next->fork_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		printphilo(philo);
	}
}

time_t	now(void)
{
	struct timeval	current_time;
	time_t			mili;

	gettimeofday(&current_time, NULL);
	mili = current_time.tv_sec
		* (time_t)1000 + current_time.tv_usec / (time_t)1000;
	return (mili);
}
