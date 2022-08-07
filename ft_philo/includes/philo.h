/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:57:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/07 19:38:06 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

// ------------ Utils

int				usage(void);

t_philo			*philo_lstaddback(t_philo *phil, t_philosophers *philos, int i);

t_philo			*philo_addlast(t_philo *philo, t_philosophers *philos, int i);

t_philo			*create_philos(char **av, t_philosophers *philos);

t_philosophers	*set_data(int ac, char **av);

void	        free_philos(t_philosophers *philos);

int		        check_args(char **av);

int		        ft_isdigit(int c);

long int        ft_atoi(const char *nptr);

char 			get_Timestamp();

// ------------ Threads

int 			try_fork_locker(t_philo *philo);

void 			fork_unlocker(t_philo *philo);

void* 			routine(void* args);

void 			thread_process(t_philosophers *philos);

int				no_death(t_philo *philo);

#endif

