/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:57:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 12:55:39 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

// ---------- UTILS

int				usage(void);

void			print_data(t_philosophers *philos);

void* 			routine(void *args);

void 			*log_philo(void *args);

t_philosophers	*get_struct(void);

t_philosophers	*get_struct(void);

t_philo			*philo_lstaddback(t_philo *phil, t_philosophers *philos, int i);

t_philo			*philo_addlast(t_philo *philo, t_philosophers *philos, int i);

t_philo			*create_philos(char **av, t_philosophers *philos);

t_philosophers	*set_data(int ac, char **av);

void			free_philos(t_philosophers *philos);

int				check_args(char **av);

int				ft_isdigit(int c);

time_t 			get_Timestamp(t_philosophers *philos);

long int		ft_atoi(const char *nptr);

// ---------- Threads Process

void 			thread_process(t_philosophers *philos);

void 			philo_process(t_philosophers *philos);

void			routine_whileeat(t_philosophers *philos, t_philo *philo);

void			routine_whiledeath(t_philosophers *philos, t_philo *philo);

// ------------ Threads Utils

int 			someone_died(t_philosophers *philos);

int 			everybody_ate(t_philosophers *philos);

int 			he_died(t_philosophers *philos, t_philo *philo);

int 			he_finished_eating(t_philosophers *philos, t_philo *philo);

int 			he_finished_sleeping(t_philosophers *philos, t_philo *philo);

int 			is_thinking(t_philosophers *philos, t_philo *philo);

int 			has_fork(t_philosophers *philos, t_philo *philo);

int 			is_sleeping(t_philosophers *philos, t_philo *philo);

void			wait_philo(t_philo *philo, t_philosophers *philos);

#endif

