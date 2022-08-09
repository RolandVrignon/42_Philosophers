/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:57:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 12:50:15 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

int		usage(void);

void	print_data(t_philosophers *philos);

void* routine(void *args);

void *log_philo(void *args);

void thread_process(t_philosophers *philos);

void philo_process(t_philosophers *philos);

t_philosophers *get_struct(void);

time_t get_Timestamp(t_philosophers *philos);

time_t now(void);

int check_health(t_philosophers *philos);

int someone_died(t_philosophers *philos);

int everybody_ate(t_philosophers *philos);

int he_died(t_philosophers *philos, t_philo *philo);

int he_finished_eating(t_philosophers *philos, t_philo *philo);

int he_finished_sleeping(t_philosophers *philos, t_philo *philo);

int is_thinking(t_philosophers *philos, t_philo *philo);

int has_fork(t_philosophers *philos, t_philo *philo);

int is_sleeping(t_philosophers *philos, t_philo *philo);

t_philo	*philo_lstaddback(t_philo *phil, t_philosophers *philos, int i);

t_philo	*philo_addlast(t_philo *philo, t_philosophers *philos, int i);

t_philo	*create_philos(char **av, t_philosophers *philos);

t_philosophers*set_data(int ac, char **av);

void	free_philos(t_philosophers *philos);

int		check_args(char **av);

int		ft_isdigit(int c);

long int	ft_atoi(const char *nptr);

void	wait_philo(t_philo *philo, t_philosophers *philos);

void	routine_whileeat(t_philosophers *philos, t_philo *philo);

void	routine_whiledeath(t_philosophers *philos, t_philo *philo);

#endif

