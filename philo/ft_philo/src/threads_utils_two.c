/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:03:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/14 23:31:35 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void util_one(t_philo *philo)
{
    t_philosophers *philos;

    philos = get_struct();
    philo->status = died;
    unlock_forks(philos, philo);
    printf("%ld %d died\n", get_tmstmp(), philo->id);
}

void util_two(t_philo *philo)
{
    philo->start_thinking_ms = 0;
    printf("%ld %d is thinking\n", get_tmstmp(), philo->id);
}

void util_three(t_philo *philo)
{
    philo->status = wait_one;
    printf("%ld %d has taken a fork\n", get_tmstmp(), philo->id);
}
void util_four(t_philo *philo)
{
    philo->status = ready_to_eat;
    printf("%ld %d has taken a fork\n", get_tmstmp(), philo->id);
}
void util_five(t_philo *philo)
{
    philo->status = eat;
    philo->start_thinking_ms = 0;
    philo->gotfork_ms = get_tmstmp();
    printf("%ld %d is eating\n", get_tmstmp(), philo->id);
}
void util_six(t_philo *philo)
{
    philo->status = sleeps;
    philo->eatsnb -= 1;
    philo->gotsleep_ms = get_tmstmp();
    pthread_mutex_unlock(&philo->fork_mutex);
    pthread_mutex_unlock(&philo->next->fork_mutex);
    printf("%ld %d is sleeping\n", get_tmstmp(), philo->id);
}

void util_seven(t_philo *philo)
{
    philo->gotsleep_ms = 0;
    philo->start_thinking_ms = get_tmstmp();
    philo->status = think;
}
