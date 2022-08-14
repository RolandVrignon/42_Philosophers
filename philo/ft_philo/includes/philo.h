/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:57:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/14 17:27:02 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

// ---------- UTILS

int				usage(void);

void			print_data(t_philosophers *philos);

t_philosophers	*get_struct(void);

t_philo			*philo_lstaddback(t_philo *phil, t_philosophers *philos, int i);

t_philo			*philo_addlast(t_philo *philo, t_philosophers *philos, int i);

t_philo			*create_philos(char **av, t_philosophers *philos, int i);

t_philosophers	*set_data(int ac, char **av);

void			free_philos(t_philosophers *philos);

int				check_args(char **av);

int				ft_isdigit(int c);

time_t			get_tmstmp(void);

time_t			now(void);

long int		ft_atoi(const char *nptr);

// ---------- Threads Process

void			lonely_process(t_philosophers *philos);

void			thread_process(t_philosophers *philos);

void			philo_process(t_philosophers *philos, t_philo *philo, int i);

void			*routine(void *args);

void			*log_philo(void *args);

// ------------ Threads Utils

int				get_status(t_philo *philo, t_status status);

void			set_status(t_philo *philo, t_status status);

int				kill_process(t_philosophers *philos, t_philo *philo);

int				someone_died(t_philosophers *philos, t_philo *philo);

int				everybody_ate(t_philosophers *philos, t_philo *philo);
#endif
