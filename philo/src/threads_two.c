/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:55:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/21 14:11:53 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	one(t_philo *philo)
{
	if (philo->eatsnb == 0)
				philo->status = done;
	if (philo->status != done && is_dead(philo))
	{
		philo->status = died;
		printf("%ld %d died\n", get_tmstmp(), philo->id);
	}
	if (philo->status == think && philo->start_thinking_ms != 0)
	{
		philo->start_thinking_ms = 0;
		printf("%ld %d is thinking\n", get_tmstmp(), philo->id);
	}
	if (philo->status == ready_to_fork && can_eat(philo))
	{
		pthread_mutex_lock(&philo->fork_mutex);
		pthread_mutex_lock(&philo->next->fork_mutex);
		philo->status = ready_to_eat;
		printf("%ld %d has taken a fork\n", get_tmstmp(), philo->id);
		printf("%ld %d has taken a fork\n", get_tmstmp(), philo->id);
	}
}

void	two(t_philo *philo)
{
	if (philo->status == ready_to_eat)
	{
		philo->status = eat;
		philo->start_thinking_ms = 0;
		philo->gotfork_ms = get_tmstmp();
		printf("%ld %d is eating\n", get_tmstmp(), philo->id);
	}
	if (philo->status == eat && finish_eating(philo))
	{
		philo->status = sleeps;
		philo->eatsnb -= 1;
		philo->gotsleep_ms = get_tmstmp();
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo->next->fork_mutex);
		printf("%ld %d is sleeping\n", get_tmstmp(), philo->id);
	}
	if (philo->status == sleeps && finish_sleeping(philo))
	{
		philo->gotsleep_ms = 0;
		philo->start_thinking_ms = get_tmstmp();
		philo->status = think;
	}
}

int	everybody_ate(t_philo *philo, int nb)
{
	int				i;

	i = 0;
	philo = philo->next;
	while (i < nb)
	{
		if (!get_status(philo, done))
			return (0);
		philo = philo->next;
		i++;
	}
	if (!get_status(philo, done))
		return (0);
	return (1);
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
