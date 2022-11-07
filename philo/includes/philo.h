/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:57:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/11/07 17:19:04 by rvrignon         ###   ########.fr       */
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

int				ft_strncmp(const char *s1, const char *s2, size_t n);

char			*ft_itoa(long long int n);

size_t			ft_strlen(const char *s);

// ---------- Threads Process

void			lonely_process(t_philosophers *philos);

void			thread_process(t_philosophers *philos);

int				philo_process(t_philosophers *philos, t_philo *philo);

int				philo_thread_create(t_philosophers *philos, t_philo *philo);

int				philo_thread_join(t_philosophers *philos, t_philo *philo);

void			destroy_all_philos_mutex(t_philosophers *philos, t_philo *philo);

void			detach_all_philos(t_philosophers *philos, t_philo *philo);

void			*routine(void *args);

void			*log_philo(void *args);

// ------------ Threads Utils

int				get_status(t_philo *philo, t_status status);

void			set_finish(t_philosophers *philos);

int				someone_died(t_philosophers *philos);

int				is_dead(t_philo *philo);

int				can_eat(t_philo *philo);

int				finish_eating(t_philo *philo);

int				finish_sleeping(t_philo *philo);

void			define_status(t_philo *philo);

void			define_status_two(t_philo *philo);

void			printphilo(t_philo *philo);

#endif
