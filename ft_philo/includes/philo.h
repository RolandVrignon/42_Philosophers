/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:57:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 18:46:03 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

int					usage(void);

void* 				routine(void *args);

void 				philo_process(t_philosophers *philos);

void 				thread_process(t_philosophers *philos);

t_philo				*philo_lstaddback(t_philo *phil, t_philosophers *philos, int i);

t_philo				*philo_addlast(t_philo *philo, t_philosophers *philos, int i);

t_philo				*create_philos(char **av, t_philosophers *philos);

t_philosophers		*set_data(int ac, char **av);

void				free_philos(t_philosophers *philos);

int					check_args(char **av);

int					ft_isdigit(int c);

long int 			ft_atoi(const char *nptr);

void				printf_Mutex(t_philosophers *philos, pthread_mutex_t printfMutex);

t_philosophers		*get_struct(void);

void				print_data(t_philosophers *philos);

time_t				now(void);

time_t 				get_Timestamp(t_philosophers *philos);

#endif

