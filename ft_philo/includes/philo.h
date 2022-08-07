/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:57:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/07 19:11:39 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

int		usage(void);

char get_Timestamp();

int try_locker(t_philo *philo);

void* routine(void* args);

void thread_process(t_philosophers *philos);

t_philo	*philo_lstaddback(t_philo *phil, t_philosophers *philos, int i);

t_philo	*philo_addlast(t_philo *philo, t_philosophers *philos, int i);

t_philo	*create_philos(char **av, t_philosophers *philos);

t_philosophers*set_data(int ac, char **av);

void	free_philos(t_philosophers *philos);

int		check_args(char **av);

int		ft_isdigit(int c);

long intft_atoi(const char *nptr);

#endif

